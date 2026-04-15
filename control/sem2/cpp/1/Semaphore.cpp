#include <thread>

// хотим задать количество потоков, которые могут работать
// если количество больше, заставляем подошедший поток ждать
// иначе впускаем и уменьшаем счетчик
// когда поток уходит он освобождает счетчик

template<class Predicate>
void wait(std::condition_variable& cond_var, std::unique_lock<std::mutex>& lock, Predicate pred ) {
    // ждем пока нас не пробудят. Как только нас пробудят, мы перейдем на следующую итерацию цикла и сразу же проверим предикат, тогда
    // если он выполнится, то мы выйдем и разрешим работу, а иначе - уснем вновь
    do {
        cond_var.wait(lock);
    } while (!pred());
}

class Semaphore {
public:
    Semaphore(const int max_num) : count(max_num) {}

    void enter() {
        std::unique_lock<std::mutex> lock(mutex_);
        cv_.wait(lock, [this] { return count > 0; });
        count.fetch_sub(1);
    }

    void leave() {
        count.fetch_add(1);
        cv_.notify_one();
    }

private:
    std::atomic<int> count;
    std::condition_variable cv_;
    std::mutex mutex_;
};