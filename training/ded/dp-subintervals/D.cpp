#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector dp(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1] = 2;
        if (s[i] == s[i + 1]) dp[i][i + 1] = 3;
    }

    for (int length = 3; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;

            if (s[l] == s[r]) {
                dp[l][r] = dp[l + 1][r] + dp[l][r - 1] + 1;
            } else {
                dp[l][r] = dp[l + 1][r] + dp[l][r - 1] - dp[l + 1][r - 1];  // формула включений исключений
            }
        }
    }

    std::cout << dp[0][n - 1];
}