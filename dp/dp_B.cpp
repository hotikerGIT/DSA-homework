#include <iostream>
#include <vector>

int main() {
    int m, n;

    std::cin >> m >> n;

    std::vector<std::vector<int>> time(m, std::vector<int>(n));
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            std::cin >> time[i][j];
        }
    }

    std::vector<int> res(m);
    dp[1][1] = time[0][0];
    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]) + time[i - 1][j - 1];

            if (j == n) {
                res[i - 1] = dp[i][j];
            }
        }
    }

    for (int num : res) {
        std::cout << num << " ";
    }
    return 0;
}