#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int v1, v2, t, d;
    std::cin >> v1 >> v2 >> t >> d;

    std::vector<int> dp(t, 0);
    dp[0] = v1;
    dp[t - 1] = v2;

    for (int i = t - 2; i > 0; --i) {
        dp[i] = dp[i + 1] + d;
    }

    int res = dp[0];
    for (int i = 1; i < t; ++i) {
        dp[i] = std::min(dp[i], dp[i - 1] + d);
        res += dp[i];
    }

    std::cout << res;
    return 0;
}