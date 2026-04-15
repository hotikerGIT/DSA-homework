#include <vector>
#include <iostream>

int main() {
    const long long mod = 1000000007;

    int n;
    std::cin >> n;

    std::vector<int> p;
    for (int i = 0; i < n; ++i) {
        std::cin >> p[i];
    }

    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(3,0));
    dp[1][2] = 1;
}