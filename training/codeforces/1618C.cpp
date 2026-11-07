#include <iostream>
#include <vector>
#include <numeric>
#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    int gcd1 = a[0];
    int gcd2 = a[1];
    for (int i = 0; i < n; i += 2) gcd1 = std::gcd(gcd1, a[i]);
    for (int i = 1; i < n; i += 2) gcd2 = std::gcd(gcd2, a[i]);

    bool flag1 = true;
    bool flag2 = true;
    for (int i = 0; i < n; i += 2) {
        flag1 &= a[i] % gcd2 != 0;
    }

    for (int i = 1; i < n; i += 2) {
        flag2 &= a[i] % gcd1 != 0;
    }

    if (!flag1 && !flag2) {
        std::cout << "0\n";
        return;
    }

    if (flag1) {
        std::cout << gcd2 << '\n';
        return;
    }

    std::cout << gcd1 << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}