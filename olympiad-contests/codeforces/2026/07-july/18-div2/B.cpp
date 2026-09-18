#include <iostream>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n, k, m;
        std::cin >> n >> k >> m;

        if (k > m) {
            std::cout << "NO\n";
            continue;
        }

        std::cout << "YES\n";

        for (int i = 0; i < n - 1; ++i) {
            std::cout << 1 << ' ';
        }

        std::cout << m - k + 1;
        std::cout << std::endl;
    }
}