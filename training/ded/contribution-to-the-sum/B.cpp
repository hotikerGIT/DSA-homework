#include <vector>
#include <iostream>
#define int long long

signed main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector intervals(n + 1, std::vector<int>(n + 1, 1e13));
    for (int i = 0; i < m; ++i) {
        int l, r, c;
        std::cin >> l >> r >> c;
        intervals[l][r] = std::min(intervals[l][r], c);
    }

    std::vector dp(n + 1, std::vector<int>(n + 1, 1e13));
    dp[0][0] = 0;

    for (int right = n; right > 0; --right) {
        for (int left = right; left > 0; --left) {

        }
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= i; ++j) {
            dp[i][j] = dp[i - 1][j];

            for (int left = i; left >= i - j; --left) {
                dp[i][j] = std::min(dp[i][j], intervals[left][i] + dp[left][j - (i - left + 1)]);
            }

            for (int fix = n - 1; fix >= 0; --fix) {
                dp[i][fix] = std::min(dp[i][fix + 1], dp[i][fix]);
            }
        }
    }

    std::cout << dp[n][k];
}