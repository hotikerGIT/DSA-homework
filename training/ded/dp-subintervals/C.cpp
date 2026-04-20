#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    int MOD = 1e9 + 9;

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        int k, m;
        std::cin >> k >> m;
        a[i] = {k, m};
    }
    std::vector dp(n + 1, std::vector<int>(n + 1, 1e18));
    for (int i = 0; i < n; ++i) dp[i][i] = 0;
    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1] = a[i].first * a[i].second * a[i + 1].second;
    }

    for (int length = 3; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;

            for (int k = l; k < r; ++k) {
                dp[l][r] = std::min(dp[l][k] + dp[k + 1][r] + a[l].first * a[k].second * a[r].second, dp[l][r]);
            }
        }
    }

    std::cout << dp[0][n - 1] % MOD;
}