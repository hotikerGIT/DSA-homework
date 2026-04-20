#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector dp(n + 1, std::vector<int>(n + 1));
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    for (int i = 0; i < n - 1; ++i) {
        dp[i][i + 1] = 1;
        if (s[i] == s[i + 1]) dp[i][i + 1] = 2;
    }

    for (int length = 3; length <= n; ++length) {
        for (int l = 0; l + length <= n; ++l) {
            int r = l + length - 1;

            dp[l][r] = std::max(dp[l + 1][r], dp[l][r - 1]);
            if (s[l] == s[r]) dp[l][r] = std::max(dp[l][r], dp[l + 1][r - 1] + 2);
        }
    }

    std::string result;
    int l = 0, r = n - 1;

    while (l < r) {
        if (s[l] == s[r] && dp[l][r] == dp[l + 1][r - 1] + 2) {
            result.push_back(s[l]);
            l++;
            r--;
        }
        else if (dp[l][r] == dp[l + 1][r]) {
            l++;
        }
        else {
            r--;
        }
    }

    std::string final_result = result;
    if (l == r) {
        final_result += s[l];
    }
    std::reverse(result.begin(), result.end());
    final_result += result;

    std::cout << final_result.size() << '\n';
    std::cout << final_result;
}