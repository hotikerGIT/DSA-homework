#include <atomic>

class TASSpinlock {
private:
    std::atomic<bool> is_locked{false};

public:
    TASSpinlock() = default;

    void lock() {
        while (is_locked.exchange(true)) {}
    }

    void unlock() {
        is_locked = false;
    }
};

class TicketSpinlock {
private:
    std::atomic<int> ticket{0}, serving{0};

public:
    TicketSpinlock() = default;

    void lock() {
        int my_ticket = ticket.fetch_add(1);

        while (my_ticket != serving) {}
    }

    void unlock() {
        serving += 1;
    }
};