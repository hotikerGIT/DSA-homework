#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    int MOD = 998244353;

    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector dp(n + 1, std::vector<int>(3, 0));
    std::vector pref(n + 1, std::vector<int>(3, 0));
    dp[1][s[0] - 'a'] = 1;
    pref[1][s[0] - 'a'] = 1;

    for (int i = 2; i <= n; ++i) {
        auto& ref = dp[i][s[i - 1] - 'a'];
        ref++;
        for (int j = 0; j < 3; ++j) {
            pref[i][j] = pref[i - 1][j];

            if (j != s[i - 1] - 'a') {
                ref += pref[i - 1][j];
            }

            ref %= MOD;
        }

        pref[i][s[i - 1] - 'a'] += ref;
        pref[i][s[i - 1] - 'a'] %= MOD;
    }

    std::cout << (pref[n][0] + pref[n][1] + pref[n][2]) % MOD;
}