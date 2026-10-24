#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int n, k, m;
    std::cin >> n >> k >> m;
    std::vector<int> cost(n), energy(n), time(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cost[i];
        std::cin >> energy[i];
        std::cin >> time[i];
    }

    std::vector dp(n + 1, std::vector(k + 1, std::vector(m + 1, 0)));
    std::vector take(n + 1, std::vector(k + 1, std::vector(m + 1, -1)));

    for (int i = 1; i <= n; ++i) {
        for (int j = k; j >= 0; --j) {
            for (int p = m; p >= 0; --p) {
                if (dp[i][j][p] < dp[i - 1][j][p]) {
                    dp[i][j][p] = dp[i - 1][j][p];
                    take[i][j][p] = take[i - 1][j][p];
                }

                if (j - energy[i - 1] < 0 ||
                    p - time[i - 1] < 0) continue;

                int next = dp[i - 1][j - energy[i - 1]][p - time[i - 1]] + cost[i - 1];
                if (dp[i][j][p] < next) {
                    dp[i][j][p] = next;
                    take[i][j][p] = i;
                }
            }
        }
    }

    std::cout << dp.back().back().back() << '\n';
    int index = take.back().back().back();
    std::vector<int> res;
    while (index > 0) {
        res.push_back(index);
        k -= energy[index - 1];
        m -= time[index - 1];
        index = take[index - 1][k][m];
    }

    std::sort(res.begin(), res.end());

    for (int num : res) std::cout << num << ' ';
}