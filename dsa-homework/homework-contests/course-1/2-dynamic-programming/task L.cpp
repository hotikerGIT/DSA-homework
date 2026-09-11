#include <vector>
#include <iostream>
#include <algorithm>


int main() {
    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::vector<long long> prefix(n - m + 1);
    long long sum = 0;
    for (int i = 0; i < m; ++i) {
        sum += p[i];
    }

    for (int i = 0; i < n - m + 1; ++i) {
        prefix[i] = sum;
        sum = sum - p[i] + p[i + m];
    }

    std::vector<std::vector<long long>> dp(n - m + 1, std::vector<long long>(k + 1, 0));
    dp[0][1] = prefix[0];

    for (int i = 1; i < n - m + 1; ++i) {
        if (i < m) {
            dp[i][1] = std::max(dp[i - 1][1], prefix[i]);
            continue;
        }

        int j = 1;
        while (j < k && dp[i - m][j] != 0) {
            dp[i][j] = std::max(dp[i - m][j - 1] + prefix[i], dp[i - 1][j]);
            j++;
        }

        dp[i][j] = std::max(dp[i - m][j - 1] + prefix[i], dp[i - 1][j]);
    }

    std::cout << dp[n - m][k];

}