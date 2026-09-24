#include <iostream>
#include <queue>
#include <string>

class MinQueue {
private:
    std::deque<int> queue;

public:
    void add(int a) {
        while (!queue.empty() && queue.back() > a) queue.pop_back();
        queue.push_back(a);
    }

    void pop(int a) {
        if (!queue.empty() && queue.front() == a) queue.pop_front();
    }

    int min() {
        return queue.empty() ? 1e9 : queue.front();
    }
};

int main() {
    int q;
    std::cin >> q;
    auto mq = MinQueue();

    for (int i = 0; i < q; ++i) {
        std::string type;
        int num;
        std::cin >> type;

        if (type == "ADD") {
            std::cin >> num;
            mq.add(num);
        }

        if (type == "POP") {
            std::cin >> num;
            mq.pop(num);
        }

        if (type == "MIN") {
            if (mq.min() == 1e9) {
                std::cout << "QUEUE IS EMPTY\n";
                continue;
            }

            std::cout << mq.min() << '\n';
        }
    }
}