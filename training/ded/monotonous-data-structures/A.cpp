#include <iostream>
#include <vector>
#include <stack>
#include <string>

struct MinStack {
    std::stack<int> stack, min;

    void push(int val) {
        stack.push(val);

        if (min.empty()) min.push(val);
        else min.push(std::min(min.top(), val));
    }

    void pop() {
        if (stack.empty()) return;
        stack.pop();
        min.pop();
    }

    int get_min() const {
        return stack.empty() ? 2e9 : min.top();
    }
};

int main() {
    int q;
    std::cin >> q;
    MinStack ms;

    for (int i = 0; i < q; ++i) {
        std::string type;
        std::cin >> type;

        if (type == "ADD") {
            int val;
            std::cin >> val;
            ms.push(val);
        }

        else if (type == "POP") {
            ms.pop();
        }

        else {
            int res = ms.get_min();

            if (res == 2e9) {
                std::cout << "STACK IS EMPTY\n";
            } else {
                std::cout << res << '\n';
            }
        }
    }
}