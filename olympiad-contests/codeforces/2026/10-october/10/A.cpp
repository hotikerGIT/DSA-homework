#include <iostream>

void solve() {
    int x, y;
    std::cin >> x >> y;

    if (y > x + 1) {
        std::cout << -1 << std::endl;
        return;
    }

    if (x < y) {
        std::cout << y << std::endl;
        return;
    }

    std::cout << x + (y % 2 != x % 2) << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}