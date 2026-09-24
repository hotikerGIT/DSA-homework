#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string a, b;
    std::cin >> a >> b;

    std::vector<int> s(a.size());

    for (int i = 0; i < a.size(); ++i) {
        s[i] = (10 + a[i] - b[i]) % 10;
    }

    std::vector dp(std::vector(std::vector<int>(10, 1e9), 2), s.size() + 1);
    for (int i = 0; i < 2; ++i) {
        for (int digit = 0; digit < 10; ++digit) {
            dp[0][i][digit] = 0;
        }
    }

    for (int i = 0; i < s.size(); ++i) {
        dp[i + 1][1 - 1][s[i]] = dp[i][1 - 1][0] + 1;
        dp[i + 1][2 - 1][s[i]] = dp[i][2 - 1][0] + 1;
        dp[i + 1][2 - 1][s[i]] =

        for (int digit = 1; digit < 10; ++digit) {
            dp[i + 1][1 - 1][digit] = dp[i][1 - 1][s[i]] + 1 - (s[i] == digit);
            dp[i + 1][]
        }
    }
}