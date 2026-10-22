#include <iostream>
#include <vector>

int main() {
    int m, n, k;
    std::cin >> m >> n >> k;
    std::vector<std::vector<int>> matrix(m, std::vector<int>(n));
    for (auto& row : matrix) for (auto& x : row) std::cin >> x;

    std::vector dp(m, std::vector (n, std::vector<int>(2, -1e9)));
    dp[0][0][0] = 0;

    for (int i = 1; i < m; ++i) {
        for (int j = 1; j < n; ++j) {
            int ind1 = i - k;

            if (ind1 >= 0) {
                dp[i][j][0] = std::max(
                        dp[i][j][0],
                        dp[ind1][j - 1][1] + 3 * matrix[i][j]
                );

                dp[i][j][1] = std::max(
                        dp[i][j][1],
                        dp[ind1][j - 1][0] + matrix[i][j]
                );
            }

            int ind2 = j - k;
            if (ind2 >= 0) {
                dp[i][j][0] = std::max(
                        dp[i][j][0],
                        dp[i - 1][ind2][1] + 3 * matrix[i][j]
                );

                dp[i][j][1] = std::max(
                        dp[i][j][1],
                        dp[i - 1][ind2][0] + matrix[i][j]
                );
            }
        }
    }

    int ans = std::max(dp.back().back()[0], dp.back().back()[1]);
    std::cout << std::max(-1, ans);
}