#include <iostream>
#define int long long

signed main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n;
        std::cin >> n;

        if (n == 1) {
            std::cout << "1\n";
            continue;
        }

        if (n == 2) {
            std::cout << "-1\n";
            continue;
        }

        int a = 1, b = 2, c = 3;
        std::cout << 1 << ' ' << 2 << ' ' << 3 << ' ';

        for (int i = 4; i <= n; ++i) {
            c *= 2;
            std::cout << c << ' ';
        }
        std::cout << '\n';
    }
}