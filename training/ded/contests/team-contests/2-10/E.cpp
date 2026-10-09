#include <iostream>
#include <vector>
#define int long long

signed main() {
    int m;
    std::cin >> m;

    std::vector<int> dp(1e6 + 2, 2e9);
    dp[1] = 1;

    for (int i = 2; i < dp.size(); ++i) {
        dp[i] = std::min(dp[i], dp[i - 1] + 1);

        for (int j = 1; j <= i && i * j <= 1e6; ++j) {
            dp[i * j] = std::min(dp[i * j], dp[i] + 1);
        }
    }

    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        std::cout << dp[x] << '\n';
    }
}