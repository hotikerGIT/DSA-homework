#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(n + 1));

    for (int i = 1; i <= n; ++i) {
        dp[0][i] = dp[0][i - 1] + i * a[n - i];
        dp[i][0] = dp[i - 1][0] + i * a[i - 1];

        for (int j = 1; j < i; ++j) {
            dp[j][i - j] = std::max(dp[j - 1][i - j] + i * a[j - 1], dp[j][i - j - 1] + i * a[n - (i - j)]);
        }
    }

    int ans = 0;
    for (int i = 0; i <= n; ++i) {
        ans = std::max(ans, dp[i][n - i]);
    }
    std::cout << ans;
}