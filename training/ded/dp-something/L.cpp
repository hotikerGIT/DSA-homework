#include <iostream>
#include <vector>

int main() {
    int n, k, m;
    std::cin >> n >> k >> m;
    std::vector<int> cost(n), energy(n), time(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> cost[i];
        std::cin >> energy[i];
        std::cin >> time[i];
    }

    std::vector dp(k + 1, std::vector(m + 1, 0));
    std::vector take(k + 1, std::vector(m + 1, -1));

    for (int i = 0; i < n; ++i) {
        for (int j = k; j - energy[i] >= 0; --j) {
            for (int p = m; p - time[i] >= 0; --p) {
                int next = dp[j - energy[i]][p - time[i]] + cost[i];
                if (dp[j][p] < next) {
                    dp[j][p] = next;
                    take[j][p] = i;
                }
            }
        }
    }

    std::cout << dp.back().back() << '\n';
    int index = take.back().back();
    std::vector<int> res;
    while (index != -1) {
        res.push_back(index);
        k -= energy[index];
        m -= time[index];
        index = take[k][m];
    }

    for (int i = res.size() - 1; i >= 0; --i) {
        std::cout << res[i] + 1 << ' ';
    }
}