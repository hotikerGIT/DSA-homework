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
    int n, q;
    std::cin >> n >> q;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) pref[i + 1] = pref[i] + a[i];

    std::vector<int> pref_pref(n + 1);
    for (int i = 0; i < n; ++i) pref_pref[i + 1] = pref_pref[i] + pref[i + 1];

    auto bp = [&](int left, int right, int check) {
        int ans = 0;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (mid * (mid + 1) / 2 + 1 <= check) {
                ans = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return ans;
    };

    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;

        int left = bp(1, n, l);
        int right = bp(1, n, r);

        int ans = pref_pref[right] - pref_pref[left];
        ans += pref[r - right * (right + 1) / 2];
        ans -= pref[l - left * (left + 1) / 2 - 1];

        std::cout << ans << '\n';
    }
}