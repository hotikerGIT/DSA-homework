#include <vector>
#include <iostream>
#include <string>
#include <limits>

std::string reverseString(std::string str) {
    std::string reversed = "";
    for (int i = str.length() - 1; i >= 0; i--) {
        reversed += str[i];
    }
    return reversed;
}

int main() {
    int n;
    std::cin >> n;

    const long long LIMIT = std::numeric_limits<long long>::max() - std::numeric_limits<int>::max();

    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> c[i];
    }

    std::vector<std::string> strings(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
    }

    std::vector<std::pair<long long, long long>> dp(n, std::pair<long long, long long>(LIMIT, LIMIT));
    dp[0] = {0, c[0]};

    bool neg_flag = false;
    for (int i = 1; i < n; ++i) {
        if (dp[i - 1].first == LIMIT && dp[i - 1].second == LIMIT) {
            neg_flag = true;
            break;
        }

        std::string reversed_previous = reverseString(strings[i - 1]);
        std::string reversed_current = reverseString(strings[i]);

        if (strings[i - 1] <= strings[i]) {
            dp[i].first = dp[i - 1].first;
        }

        if (reversed_previous <= strings[i]) {
            dp[i].first = std::min(dp[i].first, dp[i - 1].second);
        }

        if (strings[i - 1] <= reversed_current) {
            dp[i].second = dp[i - 1].first + c[i];
        }

        if (reversed_previous <= reversed_current) {
            dp[i].second = std::min(dp[i].second, dp[i - 1].second + c[i]);
        }
    }

    long long res = std::min(dp[n - 1].first, dp[n - 1].second);
    if (!neg_flag && res != LIMIT) {
        std::cout << res;
    }
    else {
        std::cout << -1;
    }
}