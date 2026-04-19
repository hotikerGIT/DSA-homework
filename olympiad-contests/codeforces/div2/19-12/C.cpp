#include <iostream>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;
        if (k == 1) {
            std::cout << n;
            continue;
        }

        for (int i = 0; i < k - 2; ++i) {
            std::cout << n << ' ';
        }

        if (k % 2 == 1) {
            std::cout << n << ' ' << n << std::endl;
            continue;
        }

        int log = 1;
        int power = 0;
        while (log <= n) {
            log <<= 1;
            power++;
        }
        log >>= 1;
        power--;

        int first = log;
        int second = 0;

        for (int i = power - 1; i >= 0; --i) {
            second += 1 << i;

            if ((n & (1 << i)) == 0) {
                first += 1 << i;

                if (first >= n) {
                    first -= 1 << i;
                    second -= 1 << i;
                }
            }
        }

        std::cout << first << ' ' << second << std::endl;
    }
}