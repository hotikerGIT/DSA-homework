#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, k;
    std::cin >> n >> k;

    long long mod = 1000000007;

    std::unordered_map<int, std::vector<int>> graph;
    for (int i = n; i > 0; --i) {
        for (int j = i; j <= n; ++j) {
            if (j % i == 0) {
                graph[i].push_back(j);
            }
        }
    }

    std::vector<std::vector<long long>> dp(k, std::vector<long long>(n + 1, 0));
    for (int i = 1; i < n + 1; ++i) {
        dp[0][i] = 1;
    }

    for (int i = 1; i < k; ++i) {
        for (int j = n; j > 0; --j) {
            long long sum = 0;

            for (int path : graph[j]) {
                sum = (sum + dp[i - 1][path]) % mod;
            }

            dp[i][j] = sum;
        }
    }

    long long res = 0;
    for (int i = 1; i < n + 1; ++i) {
        res += dp[k - 1][i];
    }

    std::cout << res % mod;
}