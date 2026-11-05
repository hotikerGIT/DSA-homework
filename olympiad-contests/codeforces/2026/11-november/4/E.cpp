#include <iostream>
#include <string>
#include <vector>
#define int long long

int mod = 998244353;

int bin_pow(int num, int pow) {
    if (pow == 0) return 1;
    if (pow % 2 == 1) return num * bin_pow(num, pow - 1) % mod;
    int half = bin_pow(num, pow / 2);
    return half * half % mod;
}

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> dp(n + 1), amount(n + 1);
    dp[0] = 0;
    amount[0] = 1;
    int frees = 0;

    for (int i = 1; i <= n; ++i) {
        int best = dp[i - 1];

        if (i >= 2) {
            std::string t;
            t += s[i - 2];
            t += s[i - 1];

            if (t == "01" || t == "10") {
                if (best <= dp[i - 2] + 2) {
                    best = dp[i - 2] + 2;
                }
            }
        }

        if (i >= 3) {
            std::string t;
            t += s[i - 3];
            t += s[i - 2];
            t += s[i - 1];

            if (t == "010" || t == "101") {
                if (best <= dp[i - 3] + 3) {
                    best = dp[i - 3] + 3;
                }
            }
        }

        dp[i] = best;

        if (i >= 2) {
            std::string t;
            t += s[i - 2];
            t += s[i - 1];

            if (t == "01" || t == "10") {
                if (dp[i] == dp[i - 2] + 2) {
                    amount[i] += amount[i - 2];
                    amount[i] %= mod;
                }
            }
        }

        if (i >= 3) {
            std::string t;
            t += s[i - 3];
            t += s[i - 2];
            t += s[i - 1];

            if (t == "010" || t == "101") {
                if (dp[i] == dp[i - 3] + 3) {
                    amount[i] += amount[i - 3];
                    amount[i] %= mod;
                }
            }
        }

        if (dp[i] == dp[i - 1]) {
            frees++;
            amount[i] += bin_pow(2, frees) - 1;
        }

    }

    std::cout << dp.back() + n << ' ' << amount.back() << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}