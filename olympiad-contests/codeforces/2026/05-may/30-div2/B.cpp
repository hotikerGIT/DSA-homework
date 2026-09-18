#include <iostream>
#include <vector>
#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n), pref(n + 1);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            pref[i + 1] = pref[i] + a[i];
        }

        for (int i = 1; i < n; ++i) {
            a[i] = std::min(a[i - 1], pref[i + 1] / (i + 1));
        }

        for (int num : a) {
            std::cout << num << ' ';
        }
        std::cout << '\n';
    }
}