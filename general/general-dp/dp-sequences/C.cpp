#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    int m;
    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) std::cin >> b[i];

    std::vector<std::vector<int>> dp_nop(n + 1, std::vector<int>(m + 1));
    std::vector<std::pair<int, int>> good;
    for (int i = 1; i < n + 1; ++i) {
        for (int j = 1; j < m + 1; ++j) {
            if (a[i - 1] == b[j - 1]) {
                dp_nop[i][j] = dp_nop[i - 1][j - 1] + 1;

                if (dp_nop[i][j] > std::max(dp_nop[i - 1][j], dp_nop[i][j - 1])) {
                    good.emplace_back(a[i - 1], j);
                }
            }

            else {
                dp_nop[i][j] = std::max(dp_nop[i - 1][j], dp_nop[i][j - 1]);
            }
        }
    }

    if (good.empty()) {
        std::cout << 0;
        return 0;
    }

    std::vector<std::vector<int>> dp(good.size());
    for (int i = 0; i < good.size(); ++i) {
        int best_index = -1;
        for (int j = i - 1; j >= 0; --j) {
            if (good[i].first <= good[j].first || good[i].second <= good[j].second) {
                continue;
            }

            if (best_index == -1 || dp[j].size() > dp[best_index].size()) {
                best_index = j;
            }
        }

        if (best_index > -1) {
            for (int num : dp[best_index]) {
                dp[i].push_back(num);
            }
        }

        dp[i].push_back(good[i].first);
    }

    int best_index = 0;
    for (int i = 0; i < dp.size(); ++i) {
        if (dp[i].size() > dp[best_index].size()) {
            best_index = i;
        }
    }

    std::cout << dp[best_index].size() << '\n';
    for (int num : dp[best_index]) {
        std::cout << num << ' ';
    }
}