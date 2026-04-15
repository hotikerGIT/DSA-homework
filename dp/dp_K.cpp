#include <vector>
#include <iostream>

int main() {
    const long long mod = 1000000007;
    int t, k;
    std::cin >> t >> k;

    std::vector<long long> dp(100001, 0);
    dp[0]++;

    for (int i = 1; i < 100001; ++i) {
        dp[i] = dp[i - 1];

        if (i - k >= 0) {
            dp[i] = (dp[i] + dp[i - k]) % mod;
        }
    }

    std::vector<long long> prefix(100001, 0);
    for (int i = 1; i < 100001; ++i) {
        prefix[i] = prefix[i - 1] + dp[i];
    }

    int a, b;
    for (int i = 0; i < t; ++i) {
        std::cin >> a >> b;
        long long ans = (prefix[b] - prefix[a - 1]) % mod;
        std::cout << ans << std::endl;
    }

    return 0;
}