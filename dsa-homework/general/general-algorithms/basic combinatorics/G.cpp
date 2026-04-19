#include <iostream>
#include <cmath>

int main() {
    int t, n, k;
    long long mod = std::pow(10, 9) + 7;
    std::cin >> t;

    while (t--) {
        std::cin >> n >> k;
        long long res = 1;

        for (int i = 0; i < k; ++i) {
            res = (res * n) % mod;
        }

        std::cout << res << std::endl;
    }
}