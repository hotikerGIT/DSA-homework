#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long

int bin_pow(int number, int power, int mod) {
    if (power == 0) return 1;
    if (power % 2 == 1) return number * bin_pow(number, power - 1, mod) % mod;
    int half = bin_pow(number, power / 2, mod);
    return half * half % mod;
}

signed main() {
    int mod = 362880;

    int n, m;
    std::cin >> n >> m;
    std::string t, s;
    std::cin >> t >> s;

    int match = 0;
    for (int i = 0; i < n; ++i) match += s[i] == t[i];
    std::vector dp(n + 1, 0ll), next(n + 1, 0ll);
    dp[match] = 1;

    int bp = bin_pow(25, n, mod);
    for (int i = 1; i <= m; ++i) {
        std::fill(next.begin(), next.end(), 0);

        for (int j = 0; j <= n; ++j) {
            int better = j == 0 ? 0 : dp[j - 1] * (n - j + 1) % mod;
            int worse = j == n ? 0 : dp[j + 1] * 25 * (j + 1) % mod;
            int even = j == n ? 0 : dp[j] * 24 * (n - j) % mod;

            next[j] = better + worse + even;
            next[j] %= mod;

            if (j == 0) {
                for (int k = 0; k <= n; ++k) {
                    next[0] += dp[k] * bp;
                    next[0] %= mod;
                }

                next[0] = (next[0] + mod - dp[0]) % mod;

            } else if (j == n) {
                for (int k = 0; k < n; ++k) {
                    next[j] += dp[k];
                    next[j] %= mod;
                }
            }
        }

        std::swap(dp, next);
    }

    std::cout << dp.back();
    return 0;
}