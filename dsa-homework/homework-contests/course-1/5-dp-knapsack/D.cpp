#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        long long m, x;
        std::cin >> m >> x;

        std::vector<long long> cost(m);
        std::vector<long long> happiness(m);
        long long total_sum = 0;

        long long c_i, h_i;
        for (int i = 0; i < m; ++i) {
            std::cin >> c_i >> h_i;
            cost[i] = c_i;
            happiness[i] = h_i;
            total_sum += h_i;
        }

        std::vector<std::vector<long long>> dp(m + 1, std::vector<long long>(total_sum + 1, -1));
        dp[0][0] = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < total_sum + 1; ++j) {
                if (dp[i][j] < 0) {
                    continue;
                }

                dp[i + 1][j] = std::max(dp[i][j] + x, dp[i + 1][j]);

                if (dp[i][j] < cost[i]) {
                    continue;
                }

                dp[i + 1][j + happiness[i]] = std::max(dp[i + 1][j + happiness[i]], dp[i][j] - cost[i]) + x;
            }
        }

        for (long long i = total_sum; i >= 0; --i) {
            if (dp[m][i] > -1) {
                std::cout << i << std::endl;
                break;
            }
        }
    }
}