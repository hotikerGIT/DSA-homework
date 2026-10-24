#include <iostream>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;

    int cur = 0;
    bool to_left = false;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            std::cout << (j == cur ? '*' : '#');
        }

        cur += to_left ? -1 : 1;

        if (cur == m - 1) {
            to_left = true;
        }

        if (cur == 0) {
            to_left = false;
        }

        cur %= m;

        std::cout << '\n';
    }
}