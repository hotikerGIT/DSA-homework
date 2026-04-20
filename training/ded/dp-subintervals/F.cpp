#include <iostream>
#include <vector>
#include <string>
#define int long long

signed main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector dp(n + 1, std::vector<int>(n + 1, 1e9));
    std::vector last_operation(n + 1, std::vector<std::string>(n + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
        last_operation[i][i] = std::string() + s[i] + s[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        last_operation[i][i + 1] = std::string() + s[i] + s[i + 1];
        dp[i][i + 1] = 1;
        dp[i][i + 1] += s[i] != s[i + 1];
    }

    for (int length = 3; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;

            dp[l][r] = dp[l + 1][r - 1];

            std::string last = last_operation[l + 1][r - 1];
            dp[l][r] += last[0] != s[l];
            dp[l][r] += last[1] != s[r];
            last_operation[l][r] = std::string() + s[l] + s[r];
        }
    }

    std::cout << dp[0][n - 1];
}