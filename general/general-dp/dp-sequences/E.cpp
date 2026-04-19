#include <vector>
#include <string>
#include <iostream>

int main() {
    int n, m;
    std::cin >> n >> m;

    std::string a, b;
    std::cin >> a >> b;

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(m + 1, 0));

    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = 2 + dp[i - 1][j - 1];
            }

            else {
                dp[i][j] = std::max(dp[i][j], std::max(dp[i - 1][j] - 1, dp[i][j - 1] - 1));
            }

            ans = std::max(ans, dp[i][j]);
        }
    }

    std::cout << ans;
}