#include <vector>
#include <iostream>
#include <unordered_map>

int main() {
    long long n;
    std::cin >> n;

    std::vector<long long> score(n);
    for (long long i = 0; i < n; ++i) {
        std::cin >> score[i];
    }

    std::unordered_map<long long, long long> counter;
    for (long long i : score) {
        counter[i] += 1;
    }

    std::vector<long long> dp(100001, 0);
    dp[1] = counter[1];

    for (int i = 2; i < 100001; ++i) {
        dp[i] = std::max(dp[i - 2] + counter[i] * i, dp[i - 1]);
    }

    std::cout << dp[100000];
    return 0;
}