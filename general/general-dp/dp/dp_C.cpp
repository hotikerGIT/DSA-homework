#include <iostream>
#include <vector>

int main() {
    int n, a, b, c;

    std::cin >> n >> a >> b >> c;

    std::vector<int> dp(n + a + b + c, 0);

    dp[0] = 1;
    for (int i = 0; i <= n; ++i) {
        if (dp[i] == 0) continue;
        dp[i + a] = std::max(dp[i + a], dp[i] + 1);
        dp[i + b] = std::max(dp[i + b], dp[i] + 1);
        dp[i + c] = std::max(dp[i + c], dp[i] + 1);
    }

    std::cout << dp[n] - 1;
}