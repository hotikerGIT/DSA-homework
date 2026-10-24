#include <iostream>
#include <vector>
#include <string>

int main() {
    freopen("message.in", "r", stdin);
    freopen("message.out", "w", stdout);
    int k;
    std::cin >> k;
    std::string s;
    std::cin >> s;
    auto n = s.size();

    // состояние - количество символов, которые надо удалить
    std::vector dp(n, std::vector<int>(n, 1e9));
    for (int l = 0; l < n; ++l) {
        for (int r = 0; r < n; ++r) {
            if (r < l) dp[l][r] = -1;
            else if (l == r) dp[l][r] = 0;
            else if (r == l + 1) dp[l][r] = s[l] == s[r] ? 0 : 1;
        }
    }

    for (int len = 3; len <= n; ++len) {
        for (int pos = 0; pos + len <= n; ++pos) {
            int r = pos + len - 1;

            if (s[pos] == s[r]) dp[pos][r] = dp[pos + 1][r - 1];
            else dp[pos][r] = std::min(dp[pos][r - 1], dp[pos + 1][r]) + 1;
        }
    }

    for (int len = n; len > 0; --len) {
        for (int pos = 0; pos + len <= n; ++pos) {
            if (dp[pos][pos + len - 1] <= k) {
                std::cout << pos + 1 << ' ' << pos + len;
                return 0;
            }
        }
    }
}