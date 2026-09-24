#include <iostream>
#define int long long

void solve() {
    int a, b, c;
    std::cin >> a >> b >> c;

    if (a >= b) {
        std::cout << a + c - b;
    } else {
        std::cout << std::max(a + c - b, b - a);
    }

    std::cout << std::endl;
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}