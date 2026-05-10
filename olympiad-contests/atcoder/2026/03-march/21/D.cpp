#include <iostream>
#include <algorithm>
#include <deque>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::deque<int> a(n);
    for (int i = 0; i < n; i++) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    for (int i = 0; i < n; ++i){
        int diff = *a.rbegin() - a[i];
        int k_times = diff / k;
        a[i] += k_times * k;
    }
    std::sort(a.begin(), a.end());

    int ans = a[n - 1] - a[0];
    int cnt = 0;
    while (a[0] + k - a[1] <= *a.rbegin() - a[0] || cnt == n) {
        int tmp = *a.begin() + k;
        a.push_back(tmp);
        a.pop_front();
        ans = std::min(ans, a[n - 1] - a[0]);
        cnt++;
    }

    std::cout << ans;
}