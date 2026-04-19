#include <iostream>
#include <vector>
#include <set>
#define int long long

signed main() {
    int n1, n2, n3, k;
    std::cin >> n1 >> n2 >> n3 >> k;
    std::vector<int> a(k);
    for (int i = 0; i < k; ++i) std::cin >> a[i];
    std::vector<int> dp(101);

    for (int i = 0; i < dp.size(); ++i) {
        std::set<int> reachable;

        for (auto num : a) {
            if (num <= i) {
                reachable.insert(dp[i - num]);
            }
        }

        int mex = 0;
        while (reachable.count(mex)) mex++;
        dp[i] = mex;
    }

    std::cout << ((dp[n1] ^ dp[n2] ^ dp[n3]) == 0 ? "Vasya" : "Peter");
}