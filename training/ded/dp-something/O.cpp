#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> b(n), c(n);
    for (int& x : b) std::cin >> x;
    for (int& x : c) std::cin >> x;

    std::vector<int> cost(1e3 + 2, 1e9);
    cost[1] = 0;

    for (int i = 1; i <= 1e3; ++i) {
        for (int j = i; j >= 1; --j) {
            int next = i + i / j;

            if (next >= cost.size()) continue;
            cost[next] = std::min(cost[next], cost[i] + 1);
        }
    }

    int sum = 0;
    for (int num : b) sum += cost[num];

    std::vector<int> dp(std::min(k, sum) + 1);
    for (int i = 0; i < n; ++i) {
        for (int j = dp.size() - 1; j >= 0; --j) {
            int ind = j - cost[b[i]];
            if (ind < 0) continue;
            dp[j] = std::max(dp[j], dp[ind] + c[i]);
        }
    }

    std::cout << dp.back();
}