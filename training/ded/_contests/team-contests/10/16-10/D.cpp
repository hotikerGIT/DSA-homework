#include <iostream>
#include <vector>
#include <string>
#define int long long

void solve();

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n, x, y;
    std::string s;
    std::cin >> n >> x >> y >> s;

    std::vector<int> dp(n + 1, 1e18);
    dp[0] = 0;

    std::vector<std::vector<int>> cost(n, std::vector<int>(27, 0));
    for (int i = 0; i < n; ++i) {
        std::vector<int> cnt(26);
        int cur_cost = 0;

        for (int j = 1; j <= 26 && j - 1 <= i; ++j) {
            char c = s[i - j + 1];
            cnt[c - 'a']++;
            cur_cost += cnt[c - 'a'] > 1;
            cost[i][j] = cur_cost * x;
        }
    }

    for (int i = 1; i <= 26 && i <= n; ++i) {
        dp[i] = cost[i - 1][i];
    }

    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= 26 && i - j - 1 >= 0; ++j) {
            dp[i] = std::min(dp[i], y + cost[i - 1][j] + dp[i - j - 1]);
        }
    }

    std::cout << dp[n] << '\n';
}