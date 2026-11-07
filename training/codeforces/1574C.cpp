#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum += a[i];
    }
    std::sort(a.begin(), a.end());

    int m;
    std::cin >> m;
    while (m--) {
        int x, y;
        std::cin >> x >> y;

        auto it = std::upper_bound(a.begin(), a.end(), x);

        int ans = 1e18 + 1e13;
        if (it != a.end()) {
            ans = std::min(ans, std::max(0ll, y - (sum - *it)));
        }

        if (it != a.begin()) {
            it = std::prev(it);
            ans = std::min(ans, x - *it + std::max(0ll, y - (sum - *it)));
        }

        std::cout << ans << '\n';
    }
}