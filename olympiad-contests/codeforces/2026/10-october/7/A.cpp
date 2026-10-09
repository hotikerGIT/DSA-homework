#include <iostream>

void solve() {
    int x, y, r;
    std::cin >> x >> y >> r;
    std::cout << x + r << ' ' << y << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}