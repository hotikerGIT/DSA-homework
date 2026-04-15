#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<long long> a(n);
        for (int i = 0; i < n; i++) {
            std::cin >> a[i];
        }

        std::vector<long long> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
        for (long long x : primes) {
            bool flag = false;

            for (long long num : a) {
                if (num % x != 0) {
                    std::cout << x << "\n";
                    flag = true;
                    break;
                }
            }

            if (flag) {
                break;
            }
        }
    }
}