#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::unordered_map<int, std::unordered_map<int, int>> rules;
    for (int i = 0; i < k; ++i) {
        int x, y, c;
        std::cin >> x >> y >> c;

        rules[x][y] = c;
    }

    std::vector<std::vector<int>> masks(n + 1);
    for (int i = 0; i < 1 << n; ++i) {
        int mask = i;
        int bit_count = 0;

        while (mask > 0) {
            bit_count += mask & 1;
            mask /= 2;
        }

        masks[bit_count].push_back(i);
    }

    std::vector<std::vector<long long>> dp(1 << n, std::vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        dp[1 << i][i] = a[i];
    }

    long long answer = 0;
    for (int i = 1; i < m; ++i) {
        for (int mask : masks[i]) {
            for (int prev_index = 0; prev_index < n; prev_index++) {
                if (!(mask >> prev_index & 1)) continue;

                for (int new_index = 0; new_index < n; ++new_index) {
                    if (mask >> new_index & 1) continue;

                    long long add = dp[mask][prev_index] + a[new_index] + rules[prev_index + 1][new_index + 1];
                    int new_mask = mask | 1 << new_index;
                    dp[new_mask][new_index] = std::max(dp[new_mask][new_index], add);

                    if (i == m - 1) {
                        answer = std::max(answer, dp[new_mask][new_index]);
                    }
                }
            }
        }
    }

    if (m == 1) {
        std::cout << *std::max_element(a.begin(), a.end());
    }

    else {
        std::cout << answer;
    }
}