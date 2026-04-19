#include <thread>
#include <mutex>
#include <vector>
#include <queue>
#include <functional>
#include <condition_variable>
#include <atomic>
#include <stdexcept>
#include <cassert>
#include <iostream>
#include <chrono>

/*
 * Требуется написать класс ThreadPool, реализующий пул потоков, которые выполняют задачи из общей очереди.
 * С помощью метода PushTask можно положить новую задачу в очередь
 * С помощью метода Terminate можно завершить работу пула потоков.
 * Если в метод Terminate передать флаг wait = true,
 *  то пул подождет, пока потоки разберут все оставшиеся задачи в очереди, и только после этого завершит работу потоков.
 * Если передать wait = false, то все невыполненные на момент вызова Terminate задачи, которые остались в очереди,
 *  никогда не будут выполнены.
 * После вызова Terminate в поток нельзя добавить новые задачи.
 * Метод IsActive позволяет узнать, работает ли пул потоков. Т.е. можно ли подать ему на выполнение новые задачи.
 * Метод GetQueueSize позволяет узнать, сколько задач на данный момент ожидают своей очереди на выполнение.
 * При создании нового объекта ThreadPool в аргументах конструктора указывается количество потоков в пуле. Эти потоки
 *  сразу создаются конструктором.
 * Задачей может являться любой callable-объект, обернутый в std::function<void()>.
 */

class ThreadPool {
private:
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std::condition_variable cv;
    // делаем мутекс мутабл, чтобы поддерживать конст методы
    mutable std::mutex mutex_, double_terminate_mutex_;
    std::atomic<bool> running{true};

    void work() {
        // хотим чтобы потоки были активны все время, пока жив пул
        while (true) {
            std::function<void()> task;

            {
                std::unique_lock<std::mutex> lock(mutex_);
                // конд вар на два сигнала - появление таски в очереди и сигнал выключения
                cv.wait(lock, [this] { return !tasks.empty() || !running; });

                // если мы выключены и тасок нет, поток выключается
                if (tasks.empty() && !running) { return; }
                // если таски есть, забираем себе
                if (!tasks.empty()) {
                    task = tasks.front();
                    tasks.pop();
                }
            }

            // саму таску мы выполняем вне блокировки
            try {
                task();
            } catch (...) {
                std::cerr << "Error";
            }
        }
    }

public:
    explicit ThreadPool(size_t threadCount) {
        for (size_t i = 0; i < threadCount; i++) {
            threads.emplace_back([this]{ work(); });
        }
    }

    ~ThreadPool() {
        // когда умираем, выключаемся (если не выключились до этого)
        if (!running.load()) { return; }
        Terminate(false);
    }

    void PushTask(const std::function<void()>& task) {
        if (!running.load()) throw std::runtime_error("Can't push task to terminated pool!");
        {
            std::unique_lock<std::mutex> lock(mutex_);
            tasks.push(task);
        }
        cv.notify_one();
    }

    void Terminate(bool wait) {
        std::unique_lock<std::mutex> double_terminate_lock(double_terminate_mutex_);
        if (!running.load()) { return; }

        // выключаем пул
        running.store(false);

        // если ждать не будем, то опустошаем очередь
        if (!wait) {
            std::unique_lock<std::mutex> lock(mutex_);
            while (!tasks.empty()) { tasks.pop(); }
        }

        // оповещаем все потоки
        /* почему работает?
         * если мы не ждем, то очередь уже пустая - все таски выкинутые
         * все потоки просто проснутся и завершатся через return
         *
         * если ждем, то очередь может быть не пустой - тогда нам нужно
         * разбудить потоки, чтобы они выполнили все задачи и после этого
         * выключились
         */
        cv.notify_all();
        for (auto& thread : threads) {
            if (thread.joinable()) { thread.join(); }
        }
    }

    bool IsActive() const {
        return running.load();
    }

    size_t QueueSize() const {
        std::unique_lock<std::mutex> lock(mutex_);
        return tasks.size();
    }
};

// Код, помогающий в отладке

/*
 * Складывает числа на полуинтервале [from, to)
 */
uint64_t SumNumbers(uint64_t from, uint64_t to) {
    uint64_t sum = 0;
    for (uint64_t number = from; number < to; ++number) {
        sum += number;
    }
    return sum;
}

int main() {
    using namespace std::literals::chrono_literals;

    {
        ThreadPool pool(10);

        std::mutex mutex;
        uint64_t sum = 0;

        constexpr int step = 1000;
        constexpr uint64_t maxNumber = 500000000;
        for (uint64_t l = 0, r = l + step; l <= maxNumber; l = r, r = l + step) {
            if (r > maxNumber + 1) {
                r = maxNumber + 1;
            }
            pool.PushTask([&sum, &mutex, l, r]() {
                std::this_thread::sleep_for(25us);
                const uint64_t subsum = SumNumbers(l, r);
                std::lock_guard<std::mutex> lockGuard(mutex);
                sum += subsum;
            });
        }

        std::cout << "QueueSize before terminate is " << pool.QueueSize() << std::endl;
        //assert(pool.QueueSize() > 100000);
        pool.Terminate(true);
        std::cout << "Terminated. Queue size is " << pool.QueueSize() << ". IsActive: " << pool.IsActive() << std::endl;

        const uint64_t expectedSum = SumNumbers(1, maxNumber + 1);
        assert(expectedSum == sum);

        try {
            pool.PushTask([](){
                std::cout << "I am a new task!" << std::endl;
            });
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Cannot push tasks after termination" << std::endl;
        }
    }

    {
        ThreadPool pool(10);

        std::mutex mutex;
        uint64_t sum = 0;

        constexpr int step = 1000;
        constexpr uint64_t maxNumber = 500000000;
        for (uint64_t l = 0, r = l + step; l <= maxNumber; l = r, r = l + step) {
            if (r > maxNumber + 1) {
                r = maxNumber + 1;
            }
            pool.PushTask([&sum, &mutex, l, r]() {
                std::this_thread::sleep_for(25us);
                const uint64_t subsum = SumNumbers(l, r);
                std::lock_guard<std::mutex> lockGuard(mutex);
                sum += subsum;
            });
        }

        std::cout << "QueueSize before terminate is " << pool.QueueSize() << std::endl;
        //assert(pool.QueueSize() > 100000);
        pool.Terminate(false);
        std::cout << "Terminated. Queue size is " << pool.QueueSize() << ". IsActive: " << pool.IsActive() << std::endl;

        const uint64_t expectedSum = SumNumbers(1, maxNumber + 1);
        assert(expectedSum > sum);

        try {
            pool.PushTask([](){
                std::cout << "I am a new task!" << std::endl;
            });
            assert(false);
        } catch (const std::exception& e) {
            std::cout << "Cannot push tasks after termination" << std::endl;
        }
    }

    return 0;
}
