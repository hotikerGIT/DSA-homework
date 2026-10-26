#include <iostream>
#include <list>

int main() {
    int n, l, r;
    std::cin >> n >> l >> r;
    std::list<char> s;
    for (int i = 0; i < n; ++i) {
        char c;
        std::cin >> c;
        s.push_back(c);
    }

    auto left = s.begin(), right = s.begin();
    int cur = 1;
    while (cur != r) {
        ++right;

        if (cur < l) {
            ++left;
        }

        ++cur;
    }

    int m;
    std::cin >> m;
    bool reverse = false;

    auto handle_normal = [&](char head, char dir) {
        auto it = head == 'L' ? left : right;

        if (dir == 'L') {
            --it;
        } else {
            ++it;
        }
    };

    auto handle_reverse = [&](char head, char dir) {
        auto it = head == 'L' ? right : left;

        if (dir == 'L') {
            if (it == right) {

            }
        }
    };

    for (int i = 0; i < m; ++i) {
        char type;
        std::cin >> type;

        if (type == 'Q') {
            char head;
            std::cin >> head;
            if (head == 'L') {
                std::cout << *left << std::endl;
            } else {
                std::cout << *right << std::endl;
            }
        }

        if (type == 'R') {
            reverse = !reverse;
            std::swap(left, right);
        }

        if (type == 'S') {
            char head, dir;
            std::cin >> head >> dir;

            if (!reverse) {
                handle_normal(head, dir);
            } else {
                handle_reverse(head, dir);
            }
        }
    }
}