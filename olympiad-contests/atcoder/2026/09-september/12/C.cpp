#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, s, l;
    std::cin >> n >> s >> l;
    s--;
    std::vector<int> a(n);
    for (int i = 0; i < n - 1; ++i) std::cin >> a[i];

    int travel_left = 0;
    int travel_right = 0;
    int ans = 0;

    for (int left = 0; left <= s; ++left) {
        if (travel_left > l) break;

        int right = 0;
        travel_right = 0;

        while (s + right <= n - 2 && 2 * travel_left + travel_right + a[s + right] <= l) {
            travel_right += a[s + right];
            right++;
        }

        ans = std::max(ans, left + right + 1);
        if (s - left - 1 >= 0)
            travel_left += a[s - left - 1];
    }

    travel_right = 0;

    for (int right = 0; right <= n - 1 - s; ++right) {
        if (travel_right > l) break;

        int left = 0;
        travel_left = 0;

        while (s - left >= 1 && 2 * travel_right + travel_left + a[s - 1 - left] <= l) {
            travel_left += a[s - 1 - left];
            left++;
        }

        ans = std::max(ans, left + right + 1);
        if (s + right <= n - 2)
            travel_right += a[s + right];
    }

    std::cout << ans;
}