#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <cstdint>
#define int long long

int bin_pow(int number, int power, int mod) {
    number %= mod;
    if (power == 0) return 1;
    if (power % 2 == 1) return number * bin_pow(number, power - 1, mod) % mod;
    int half = bin_pow(number, power / 2, mod);
    return half * half % mod;
}

int mod_inv(int number, int mod) {
    return bin_pow(number, mod - 2, mod);
}

void solve() {
    int MAX_BIT = 30;
    int MOD = 1e9 + 7;

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> intervals(m);
    for (int i = 0; i < m; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        intervals[i] = {a, b, c};
    }
    std::sort(intervals.begin(), intervals.end(), [&](auto& a, auto& b) {
        if (a[1] != b[1]) return a[1] < b[1];
        return a[0] < b[0];
    });

    std::vector<int> cached_mod_inv(n + 1);
    for (int i = 3; i <= n; i += 2) {
        cached_mod_inv[i] = mod_inv(((i - 1) * i) % MOD, MOD) % MOD;
    }

    int ans = 0;

    for (int b = 0; b < MAX_BIT; ++b) {
        int banned_cnt = 0;

        std::vector<std::pair<int, int>> stack;
        for (auto& interval: intervals) {
            if ((interval.back() >> b) & 1) continue;

            int left = interval[0];
            while (!stack.empty() && stack.back().second >= left) {
                auto [l, r] = stack.back();
                stack.pop_back();

                left = std::min(left, l);
            }
            stack.emplace_back(left, interval[1]);
        }

        for (auto& interval : stack) {
            banned_cnt += interval.second - interval.first + 1;
        }

        int s = n - banned_cnt;
        int comb = s;
        int total = s;

        for (int i = 3; i <= n - banned_cnt; i += 2) {
            comb = (comb * ((s - (i - 1)) * (s - (i - 2)) % MOD)) % MOD;
            comb = (comb * cached_mod_inv[i]) % MOD;
            total = (total + comb) % MOD;
        }

        ans = (ans + (((bin_pow(2, banned_cnt, MOD) * total) % MOD) * bin_pow(2, b, MOD)) % MOD) % MOD;
    }

    std::cout << ans << std::endl;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}