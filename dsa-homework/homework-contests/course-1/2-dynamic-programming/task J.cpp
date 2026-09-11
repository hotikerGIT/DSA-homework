#include <iostream>
#include <vector>

int main() {
    const long long mod = 1000000007;

    int n;
    std::cin >> n;
    std::vector<int> p(n);

    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::vector<long long> dp(n);
    std::vector<long long> prefix(n + 1, 0);
    prefix[0] = 0;
    prefix[1] = 2;
    dp[0] = 2;

    for (int i = 1; i < n; ++i) {
        dp[i] = (2 + prefix[i] - prefix[p[i] - 1]) % mod;

        if (dp[i] < 0) {
            dp[i] += mod;
        }

        prefix[i + 1] = (prefix[i] + dp[i]) % mod;
    }

    std::cout << prefix[n] % mod;
}