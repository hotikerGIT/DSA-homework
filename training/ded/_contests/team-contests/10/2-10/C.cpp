#include <iostream>

void solve(int n) {
    for (int i = n; i >= 1; --i) {
        int j = 0;
        while (i + j * n <= 13 * n + 113) {
            std::cout << i + j * n << ' ';
            ++j;
        }
    }
}

int main() {
    int n, p;
    std::cin >> n >> p;

    std::cout << (n > 1 ? n : 0) << '\n';

    if (p == 2) {
        solve(n);
    }
}