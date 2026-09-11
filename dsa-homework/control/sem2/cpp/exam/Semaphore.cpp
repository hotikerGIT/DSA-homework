#include <mutex>
#include <condition_variable>

class Semaphore {
private:
    int count_;
    std::mutex mtx_;
    std::condition_variable cv_;

public:
    explicit Semaphore(int n) : count_(n) {}

    void enter() {
        std::unique_lock lock(mtx_);
        cv_.wait(lock, [&](){ return count_ > 0; });
        --count_;
    }

    void leave() {
        {
            std::lock_guard lock(mtx_);
            ++count_;
        }

        cv_.notify_one();
    }
};