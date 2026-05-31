#include <iostream>

int main() {
    int t;
    std::cin >> t;

    while (t-- ) {
        int n, x1, x2, k;
        std::cin >> n >> x1 >> x2 >> k;

        if (n == 2 || n == 3) {
            std::cout << 1 << '\n';
            continue;
        }

        int d = std::abs(x1 - x2);
        d = std::min(d, n - d);
        std::cout << d + k;

        std::cout << '\n';
    }
}