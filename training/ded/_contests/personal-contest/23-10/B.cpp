#include <iostream>
#include <vector>
#define int long long

signed main() {
    int k;
    std::cin >> k;

    int target = k * (4 * k + 1);
    // разрешено - взято - сумма
    std::vector dp(4 * k + 1, std::vector(2 * k + 1, std::vector<int>(target + 1)));
    dp[0][0][0] = 1;

    for (int i = 1; i <= 4 * k; ++i) {
        std::copy(dp[i - 1].begin(), dp[i - 1].end(), dp[i].begin());

        for (int cnt = 1; cnt <= 2 * k; ++cnt) {
            for (int sum = i; sum <= target; ++sum) {
                dp[i][cnt][sum] += dp[i - 1][cnt - 1][sum - i];
            }
        }
    }

    std::cout << dp.back().back().back() / 2;
}