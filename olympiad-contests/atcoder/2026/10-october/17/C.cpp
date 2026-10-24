#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
#define int long long

void solve();

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = 1;
    //std::cin >> t;
    while (t--) solve();
}
void solve() {
    int n, k, t;
    std::cin >> n >> k >> t;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a.begin(), a.end());

    int right = 0;
    int ans = 0;
    for (int num : a) {
        if (right > t) break;

        if (right < num) {
            int amount = (std::min(t, num) - right + k - 1) / k;
            ans += amount;
        }

        right = std::max(right , num + k);
    }

    int add = right <= t ? (t - right + k - 1) / k : 0;
    std::cout << ans + add;
}