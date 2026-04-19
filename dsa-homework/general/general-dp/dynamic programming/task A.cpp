#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iostream>

int main() {
    std::ifstream Input("input.txt");
    int n;
    Input >> n;

    std::vector<int> temp(n);
    for (int i = 0; i < n; ++i) {
        Input >> temp[i];
    }

    std::vector<std::vector<int>> dp(3, std::vector<int>(n + 1, 0));
    for (int i = 1; i < n + 1; ++i) {
        dp[0][i] = dp[0][i - 1] + 1;
        if (temp[i - 1] < 0) {
            dp[0][i]--;
        }
    }

    dp[1][n] = temp[n - 1] <= 0;
    dp[1][n - 1] = dp[1][n];
    for (int i = n - 2; i >= 0; --i) {
        dp[1][i] = dp[1][i + 1] + 1;
        if (temp[i] > 0) {
            dp[1][i]--;
        }
    }

    dp[2][0] = 2 * (int)std::pow(10, 9);
    for (int i = 1; i < n + 1; ++i) {
        dp[2][i] = std::min(dp[2][i - 1], dp[0][i] + dp[1][i]);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < n + 1; ++j) {
            std::cout << dp[i][j] << " ";
        }
        std::cout << std::endl;
    }

    std::ofstream Output("output.txt");
    int res = dp[2][n];

    if (dp[0][n] == 0) {
        res = 1;
    }

    Output << res;

    return 0;
}