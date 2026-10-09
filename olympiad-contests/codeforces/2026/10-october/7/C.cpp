#include <iostream>
#include <vector>
#include <map>
#define int long long

int cost(int i, std::vector<int>& a) {
    if (i < 4) return 1e9;
    return a[i - 4] + a[i - 2] - a[i];
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::map<int, int> cnt;
    int res = 0;

    for (int i = 4; i < n; ++i) {
        int cur_sum = cost(i, a);

        res += cnt[cur_sum];
        res += cost(i - 1, a) == cur_sum;
        res += cost(i - 3, a) == cur_sum;

        cnt[cost(i - 4, a)]++;
    }

    std::cout << res << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}