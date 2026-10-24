#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n + 1);
    a[n] = 1e9;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    std::vector<int> cnt(n);
    int cur = 0;
    int cur_cnt = 1;

    for (int i = 1; i < n + 1; ++i) {
        if (a[i] != a[i - 1]) {
            cnt[cur] = cur_cnt;
            cur++;
            cur_cnt = 1;
        } else {
            cur_cnt++;
        }
    }

    int left_sum = 0;
    int res = 0;

    for (int i = 0; i < n; ++i) {
        res += left_sum * (n - cnt[i] - left_sum) * cnt[i];
        left_sum += cnt[i];
    }

    std::cout << res;
}