#include <fstream>
#include <vector>

int main() {
    std::ifstream input("b3.in");
    std::ofstream output("b3.out");

    int m, n;
    input >> m >> n;
    std::vector<int> dp(n + 1);
    dp[0] = 1;

    for (int i = 1; i <= n; ++i) {
        dp[i] = dp[i - 1];

        if (i >= m) {
            dp[i] += dp[i - m];
        }
    }

    output << dp[n];
}