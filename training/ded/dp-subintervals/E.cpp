#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::vector dp(n + 1, std::vector<int>(n + 1, 0));
    for (int i = 0; i < n; ++i) dp[i][i] = a[i];

    for (int length = 2; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;

            for (int k = l; k < r; ++k) {
                if (dp[l][k] <= 1 || dp[k + 1][r] <= 1) {
                    dp[l][r] = std::max(dp[l][r], dp[l][k] + dp[k + 1][r]);
                } else {
                    dp[l][r] = std::max(dp[l][r], dp[l][k] * dp[k + 1][r]);
                }
            }
        }
    }

    std::cout << dp[0][n - 1];
}