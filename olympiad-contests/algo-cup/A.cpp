#include <iostream>
#include <vector>
#include <map>
#define int long long

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::map<int, int> sum_cnt;
    int target = 0;
    int cur_sum = 0;
    for (int i = 0; i < n; ++i) {
        cur_sum += a[i];
        sum_cnt[cur_sum]++;
    }


    int ans = 0;
    if (sum_cnt.contains(0)) {
        ans += sum_cnt[0] == k;
    } else {
        ans += k == 0;
    }

    for (int i = 0; i < n - 1; ++i) {
        sum_cnt[target + a[i]]--;
        target += a[i];
        sum_cnt[target + cur_sum]++;

        ans += sum_cnt[target] == k;
    }

    std::cout << ans << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while(t--) solve();
}