#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    int x, y;
    std::cin >> x >> y;

    std::vector<int> a(n), b(m);

    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    std::vector<int> pref(n + 1);
    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] + a[i];
    }

    int res = 0;
    int left = 0;
    int right = n;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (pref[mid] <= x + y * k) {
            res = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    for (int i = 0; i < m; ++i) {
        int amount = (b[i] + k - 1) / k;

        if (amount > y) {
            break;
        }

        int best = i + 1;
        x += amount * k - b[i];
        y -= amount;

        left = 0;
        right = n;
        int best_res = 0;
        while (left <= right) {
            int mid = (left + right) / 2;

            if (pref[mid] <= x + y * k) {
                best_res = mid;
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }

        res = std::max(res, best + best_res);
    }

    std::cout << res;
}