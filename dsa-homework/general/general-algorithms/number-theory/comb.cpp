#include <iostream>
#include <vector>

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> dp(n, std::vector<int>(k));
    dp[0][0] = 1;

    for (int i = 1; i < n; ++i) {
        dp[i][0] = 1;
        for (int j = 1; j < k; ++j) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < k; ++j) {
            std::cout << dp[i][j] << ' ';
        }
        std::cout << std::endl;
    }

    for (int j = 0; j < k - 1; ++j) {
        int sum = 0;
        for (int i = 0; i < n - 1; ++i) {
            sum += dp[i][j];
        }

        std::cout << "k = " << j << ' '<< sum << std::endl;
        std::cout << "C[n][k] " << dp[n - 1][j + 1] << std::endl;
        std::cout << std::endl;
    }
}