#include <iostream>
#include <vector>
#include <string>
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
    std::vector dp(m + 1, std::vector<int>(n + 1, 0ll));
    dp[0][match] = 1;

    for (int i = 1; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            int better = j == 0 ? 0 : dp[i - 1][j - 1] * (n - j + 1) % mod;
            int worse = j == n ? 0 : dp[i - 1][j + 1] * 25 * (j + 1) % mod;
            int even = j == n ? 0 : dp[i - 1][j] * 24 * (n - j) % mod;

            dp[i][j] = better + worse + even;
            dp[i][j] %= mod;

            if (j == 0) {
                for (int k = 0; k <= n; ++k) {
                    dp[i][0] += dp[i - 1][k] * bin_pow(25, n, mod);
                    dp[i][0] %= mod;
                }

                dp[i][0] = (dp[i][0] + mod - dp[i - 1][0]) % mod;

            } else if (j == n) {
                for (int k = 0; k < n; ++k) {
                    dp[i][j] += dp[i - 1][k];
                    dp[i][j] %= mod;
                }
            }
        }
    }

    std::cout << dp.back().back();
    return 0;
}