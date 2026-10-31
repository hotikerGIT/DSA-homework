#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int& num : a) std::cin >> num;

    std::vector<int> dp(n + 1);
    for (int i = 1; i <= n; ++i) {
        for (int j = i; j < n; --j) {
            dp[j] = std::max(dp[j], dp[j - i] + a[i - 1]);
        }
    }

    std::cout << dp.back();
}