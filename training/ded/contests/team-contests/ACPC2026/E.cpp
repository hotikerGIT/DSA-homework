#include <iostream>
#include <vector>
#define int long long

int MOD = 1e9 + 7;

signed main() {
    int n;
    std::cin >> n;

    std::vector<int> factorial(n + 1);

    factorial[1] = 1;
    for (int i = 2; i <= n; ++i) {
        factorial[i] = factorial[i - 1] * i;
        factorial[i] %= MOD;
    }

    std::vector<int> dp(n + 1);
    dp[0] = 2;
    dp[1] = 2;

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j < 32; ++j) {
            if (i < (1LL << j)) break;
            dp[i] += dp[i - (1 << j)];
            dp[i] %= MOD;
        }
    }

    std::cout << dp[n];
}