#include <iostream>
#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, k;
        std::cin >> n >> k;
        int ans = 0;

        for (int i = 30; i >= 0; --i) {
            if (((1 << i) - 1) * k <= n) {
                ans += i * k;
                int diff = n - ((1 << i) - 1) * k;
                ans += diff / (1 << i);

                break;
            }
        }

        std::cout << ans << '\n';
    }
}