#include <iostream>
#include <vector>
#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> value(n);
    for (int i = 0; i < n; ++i) std::cin >> value[i];

    std::vector<int> prefix(n + 1), suffix(n + 1);
    for (int i = 0; i < n; ++i) {
        prefix[i + 1] = prefix[i] + value[i];
        suffix[n - 1 - i] = suffix[n - i] + value[n - 1 - i];
    }

    std::vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = (n - 1) * value[0] - suffix[1];
    int ans = dp[1];

    for (int i = 1; i < n; ++i) {
        dp[i + 1] = dp[i] + (n - 1) * value[i] - suffix[i + 1] - prefix[i];
        ans = std::max(ans, dp[i + 1]);
    }

    std::cout << ans << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}