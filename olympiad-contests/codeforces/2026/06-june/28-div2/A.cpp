#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, c;
        std::cin >> n >> c;
        std::vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        for (int i = 0; i < n; ++i) std::cin >> b[i];

        int without_change = 0;
        for (int i = 0; i < n; ++i) {
            if (a[i] < b[i]) {
                without_change = 2e9;
                break;
            }

            without_change += a[i] - b[i];
        }

        int with_change = c;
        std::sort(a.begin(), a.end());
        std::sort(b.begin(), b.end());

        for (int i = 0; i < n; ++i) {
            if (a[i] < b[i]) {
                with_change = 2e9;
                break;
            }

            with_change += a[i] - b[i];
        }

        int ans = std::min(with_change, without_change);
        if (ans == 2e9) ans = -1;

        std::cout << ans << '\n';
    }
}