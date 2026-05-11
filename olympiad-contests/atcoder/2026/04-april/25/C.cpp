#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::map<int, int> greedy;
    std::vector<int> a(n);
    int ans = 0;

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        greedy[a[i]] += a[i];
        ans += a[i];
    }

    std::vector<int> best_sum;
    for (auto& [val, sum] : greedy) {
        best_sum.push_back(sum);
    }
    std::sort(best_sum.rbegin(), best_sum.rend());

    for (int i = 0; i < k && i < (int)best_sum.size(); ++i) {
        ans -= best_sum[i];
    }

    std::cout << ans;
}