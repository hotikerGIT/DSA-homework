#include <iostream>
#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        int ans = 0;

        for (int b = 1; b <= n; ++b) {
            ans += (n / b) * (n / b);
        }

        std::cout << ans << '\n';
    }
}