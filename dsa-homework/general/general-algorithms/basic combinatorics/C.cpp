#include <iostream>
#include <cmath>
#include <string>

int main() {
    long long t, n, i, j, k;
    std::cin >> t;

    while (t--) {
        std::cin >> n >> k;
        k--;

        i = std::floor((std::pow(1 + 8 * k, 0.5) + 1) / 2);
        j = k - i * (i - 1) / 2;

        std::string res(n, 'a');
        res[n - 1 - i] = 'b';
        res[n - 1 - j] = 'b';

        std::cout << res << "\n";
    }
}