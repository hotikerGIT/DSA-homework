#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <filesystem>
#include <iostream>
#include <future>

/*
    Вам необходимо написать функцию, которая используя std::filesystem
    Рекурсивно обойдет все поддериктории данной директории.
    На каждый файл зовет функцию callback.
*/

//void CheckDir(ThreadPool& pool, fs::path dir);
//// Вызывает ls папки dir
// Далее, как будет готов результат, обрабатываем в busy-loop результаты
// 1)если папка - позвать ls
// 2)если симлинк - не делать ничего
// 3)если файл - позвать callback
//  - одновременно мы ждем результаты нескольких запросов ls

// /* some type*/ ls(fs::path path, ThreadPool& pool);
// отправляет команду в thread_pool на ls директорииш
// Само обращение к filesystem должно происходить в thread_pool. Почему?
// в ответ мы должны узнать список файлов/папок/симлинок в этой папке

//чтобы проверить, исполнена задача или нет
//if(future.wait_for(std::chrono::seconds(0)) == std::future_status::ready) {
//  получение и обработка результата
//}

//Необходимые функции из std::filesystem
//for (const auto& entity : fs::directory_iterator(path)) - обойти все файлы и папки в директории
//bool fs::is_directory(fs::path) - вернет true если папка
//bool fs::is_symlink(fs::path) аналогично
//fs::path path - путь. можно выводить в cout


//Вам дан готовый ThreadPool, который надо использовать для решения задачи
class ThreadPool {
public:
    ThreadPool(size_t threadCount) : active_(true) {
        for (size_t i = 0; i < threadCount; ++i) {
            threads_.emplace_back([&](){ThreadFunction();});
        }
    }

    void PushTask(std::function<void()> task) {
        if (!active_) {
            throw std::exception();
        }
        {
            std::lock_guard<std::mutex> lockGuard(tasksMutex_);
            tasksQueue_.push(task);
        }
        taskPushed_.notify_one();
    }

    void Terminate() {
        active_ = false;
        taskPushed_.notify_all();
        for (auto& thread : threads_) {
            thread.join();
        }
    }

    bool IsActive() const {
        return active_;
    }

    size_t QueueSize() const {
        std::lock_guard<std::mutex> lock(tasksMutex_);
        return tasksQueue_.size();
    }
private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasksQueue_;
    mutable std::mutex tasksMutex_;
    std::condition_variable taskPushed_;
    std::atomic<bool> active_;

    void ThreadFunction() {
        while (true) {
            std::unique_lock<std::mutex> lock(tasksMutex_);
            while (tasksQueue_.empty()) {
                if (!active_) {
                    return;
                }
                taskPushed_.wait(lock);
            }
            auto task = tasksQueue_.front();
            tasksQueue_.pop();
            lock.unlock();
            task();
        }
    }
};

//////////////////////////////////////////////////////////

namespace fs = std::filesystem;

void callback(const fs::path& path) {
    std::string p = path;
    std::cout << std::string() + p + "\n";
}

std::future<std::vector<fs::path>> ls(const fs::path& path, ThreadPool& pool) {
    auto promise = std::make_shared<std::promise<std::vector<fs::path>>>();
    auto future = promise->get_future();

    pool.PushTask([promise, path]() {
        try {
            std::vector<fs::path> res;
            for (const auto& entity : fs::directory_iterator(path)) {
                res.push_back(entity);
            }
            promise->set_value(res);
        } catch (fs::filesystem_error& e) {
            promise->set_exception(std::make_exception_ptr(e));
        }
    });

    return future;
}

/* Краевые случаи в обходе
 * Нет прав доступа к файлу/папке -> исключение
 *
 * Не существует такого файла/папки -> исключение
 *
 * Пул был терминирован во время работы ЧекДир -> исключение
 *
 * Во время обхода папки одним потоком, другой поток удалил файл - ?
 * Если ЧекДир вызывается в одном потоке, и ЛС не удаляет файлов, то удаление вообще не произойдет
 * Если же ЧекДир будет использоваться в многопоточной программе, умеющей удалять файлы, тогда:
 * Поток А в ЛС зашел в директорию и начал обход
 * Поток Б (сторонний) удалил директорию
 * Поток А находится в удаленной директории, никаких файлов тут нет, но итератор что-то итерирует
 * Исключение
 */

void CheckDir(ThreadPool& pool, const fs::path& dir) {
    std::queue<std::future<std::vector<fs::path>>> processing;
    processing.push(ls(dir, pool));

    while (!processing.empty()) {
        auto future = std::move(processing.front());
        processing.pop();

        if (future.wait_for(std::chrono::seconds(0)) != std::future_status::ready) {
            processing.push(std::move(future));
            continue;
        }

        try {
            for (const auto& path : future.get()) {
                if (fs::is_symlink(path)) { continue; }

                if (fs::is_directory(path)) {
                    processing.push(ls(path, pool));
                } else if (fs::is_regular_file(path)) {
                    pool.PushTask([path] { callback(path); });
                }
            }
        } catch (fs::filesystem_error& e) {
            std::cerr << e.what() << std::endl;
        } catch (std::exception& e) {
            std::cerr << "POOL TERMINATED DURING CHECKING\n" << e.what() << std::endl;
        } catch (...) {
            std::cerr << "UNKNOWN EXCEPTION\n";
        }
    }
}

int main() {
    ThreadPool pool(3);
    CheckDir(pool, "./../"); // отсчитывает от папки с исполняемым файлом
    pool.Terminate();
}
