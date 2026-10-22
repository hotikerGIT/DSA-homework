#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

void solve();

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<int> pref_max(n + 1, 0), pref_min(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        pref_max[i + 1] = pref_max[i] + std::max(a[i] + pref_max[i], a[i] - pref_max[i]);
        pref_min[i + 1] = pref_min[i] + std::min(a[i] + pref_min[i], a[i] - pref_min[i]);
    }

    int ans = -1e18;
    for (int i = 0; i < n; ++i) {
        int best_s_abs = std::max({0LL, pref_max[i], -pref_min[i], -pref_max[i], pref_min[i]});
        ans = std::max(ans, a[i] + best_s_abs);
    }

    std::cout << ans << '\n';
}