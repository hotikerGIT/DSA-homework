#include <iostream>
#include <vector>
#include <map>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<int> diff(k);
    for (int i = 0; i < k; ++i) std::cin >> diff[i];

    std::map<int, int> dp;
    for (int num : a) {
        dp[num] = 1;

        for (int d : diff) {
            if (dp.contains(num - d)) dp[num] = std::max(dp[num], dp[num - d] + 1);
        }
    }

    int ans = 0;
    for (auto& [num, cnt] : dp) ans = std::max(ans, cnt);

    std::cout << ans;
}