#include <iostream>
#include <vector>
#include <string>

int main() {
    int t;
    std::cin >> t;

    while (t-- ){
        int n, x, s;
        std::cin >> n >> x >> s;
        std::string u;
        std::cin >> u;

        std::vector<std::vector<int>> dp(n + 1, std::vector<int>(x + 1, -1));
        dp[0][0] = 0;
        for (int i = 1; i <= n; ++i) {
            dp[i][0] = 0;

            for (int j = 1; j <= x; ++j) {
                if (dp[i-1][j] != -1)
                    dp[i][j] = std::max(dp[i][j], dp[i-1][j]);

                if (u[i - 1] == 'I' || u[i - 1] == 'A') {
                    if (dp[i - 1][j - 1] != -1) dp[i][j] = std::max(dp[i][j], dp[i - 1][j - 1] + 1);
                }

                if (u[i - 1] == 'E' || u[i - 1] == 'A') {
                    if (dp[i - 1][j] > 0) dp[i][j] = std::max(dp[i][j], dp[i - 1][j] + 1);
                }

                dp[i][j] = std::min(dp[i][j], j * s);
            }
        }

        int ans = 0;
        for (int i = 0; i <= x; ++i) ans = std::max(ans, dp[n][i]);
        std::cout << ans << '\n';
    }
}