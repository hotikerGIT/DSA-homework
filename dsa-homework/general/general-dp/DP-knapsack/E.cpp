#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    int target_sum = 0;
    for (int num : a) {
        target_sum += num;
    }

    if (target_sum % 2 == 1) {
        std::cout << 0;
        return 0;
    }

    target_sum /= 2;

    std::vector<std::vector<bool>> dp(n + 1, std::vector<bool>(target_sum + 1, false));
    dp[0][0] = true;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= target_sum; ++j) {
            if (dp[i][j]) {
                dp[i + 1][j] = true;

                if (j + a[i] <= target_sum) {
                    dp[i + 1][j + a[i]] = true;
                }
            }
        }
    }

    if (!dp[n][target_sum]) {
        std::cout << 0;
        return 0;
    }

    // гарантируем что такой найдется
    for (int i = 0; i < 16; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[j] % 2 == 1) {
                std::cout << 1 << std::endl;
                std::cout << j + 1;
                return 0;
            }

            a[j] /= 2;
        }
    }
}