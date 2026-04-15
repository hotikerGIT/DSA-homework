#include <iostream>
#include <algorithm>
#include <cmath>

int func(int x, int d) {
    return x + (d + x) / (x + 1);
}

int main() {
    int t, n, d;
    std::cin >> t;

    while(t--) {
        std::cin >> n >> d;

        bool possible = false;
        int x = std::sqrt(d) - 1;

        for (int i = std::max(0, x - 10); i <= std::min(n, x + 10); ++i) {
            if (func(i, d) <= n) {
                possible = true;
                break;
            }
        }

        if (d <= n) {
            possible = true;
        }

        std::cout << (possible ? "YES" : "NO") << "\n";
    }
}