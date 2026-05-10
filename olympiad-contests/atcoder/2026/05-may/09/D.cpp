#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n);
    int start = 1e18, end = 2e18;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        start = std::min(start, a[i]);
    }

    auto check = [&](int num) {
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            int diff = std::max(0ll, num - a[i]);

            sum += (diff + i) / (i + 1);
            if (sum > k) return false;
        }

        return true;
    };

    int ans = start;

    while (start <= end) {
        int mid = start + (end - start) / 2;

        if (check(mid)) {
            ans = mid;
            start = mid + 1;

        } else {
            end = mid - 1;
        }
    }

    std::cout << ans;
}
