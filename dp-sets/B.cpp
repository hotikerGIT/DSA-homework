#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    long long n, m, k;
    std::cin >> n >> m >> k;

    std::vector<long long> a(n);
    for (long long i = 0; i < n; ++i) std::cin >> a[i];

    std::unordered_map<long long, std::unordered_map<long long, long long>> rules;
    for (long long i = 0; i < k; ++i) {
        long long x, y, c;
        std::cin >> x >> y >> c;
        rules[x][y] = c;
    }

    std::vector<std::vector<long long>> masks(n + 1);
    for (long long i = 0; i < 1 << n; ++i) {
        long long mask = i;
        long long bit_count = 0;

        while (mask > 0) {
            bit_count += mask & 1;
            mask /= 2;
        }

        masks[bit_count].push_back(i);
    }

    std::vector<long long> dp(1 << n);
    long long answer = 0;
    for (long long i = 0; i < m; ++i) {
        for (long long mask : masks[i]) {
            for (long long index = 0; index < n; ++index) {
                if ((mask >> index) & 1) continue;
                long long addition = a[index] + dp[mask];

                for (long long j = 0; j < n; ++j) {
                    if ((mask >> j) & 1) {
                        addition += rules[index + 1][j + 1];
                    }
                }

                long long new_mask = mask | 1 << index;
                dp[new_mask] = std::max(dp[new_mask], addition);

                if (i == m - 1) {
                    answer = std::max(answer, dp[new_mask]);
                }
            }
        }
    }

    std::cout << answer;
}