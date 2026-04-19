#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    int n;

    std::cin >> n;

    std::vector<int> schedule(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> schedule[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(3));

    for (int i = 1; i < n + 1; ++i) {
        if (!(schedule[i - 1] & 1)) {
            dp[i][0] = 1000;
        }

        else {
            dp[i][0] = std::min(dp[i - 1][1], dp[i - 1][2]);
        }

        if (!(schedule[i - 1] & 2)) {
            dp[i][1] = 1000;
        }

        else {
            dp[i][1] = std::min(dp[i - 1][0], dp[i - 1][2]);
        }

        dp[i][2] = std::min({dp[i - 1][2], dp[i - 1][0], dp[i - 1][1]}) + 1;
    }

    std::cout << std::min({dp[n][0], dp[n][1], dp[n][2]});
}