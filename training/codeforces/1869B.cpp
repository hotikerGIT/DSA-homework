#include <iostream>
#include <vector>
#include <set>
#define int long long

void solve() {
    int n, k, a, b;
    std::cin >> n >> k >> a >> b;
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    std::vector<std::pair<int, int>> big(points.begin(),
                                         points.begin() + k);

    int min_a = 1e18;
    int min_b = 1e18;
    auto dist = [&](int i, int j) {
        return std::abs(points[i].first - points[j].first) +
               std::abs(points[i].second - points[j].second);
    };

    int ans = dist(a - 1, b - 1);

    for (int i = 0; i < k; ++i) {
        min_a = std::min(min_a, dist(a - 1, i));
        min_b = std::min(min_b, dist(b - 1, i));
    }

    ans = std::min(ans, min_a + min_b);
    std::cout << ans << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while( t--) solve();
}