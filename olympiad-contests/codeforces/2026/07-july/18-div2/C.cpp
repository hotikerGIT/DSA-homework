#include <iostream>
#include <vector>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n), b(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        for (int i = 0; i < n; ++i) std::cin >> b[i];

        int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
        for (int i = 0; i < n; ++i) {
            p1 += a[i] == 0 && b[i] == 0;
            p2 += a[i] == 0 && b[i] == 1;
            p3 += a[i] == 1 && b[i] == 0;
            p4 += a[i] == 1 && b[i] == 1;
        }

        if (p3 % 2 == 1) {
            std::cout << 1 << '\n';
            continue;
        }

        if (p3 % 2 == 0 && p3 > 0) {
            std::cout << 2 << '\n';
            continue;
        }

        if (p2 == 0) {
            std::cout << 0 << '\n';
            continue;
        }

        if (p4 == 0) {
            std::cout << -1 << '\n';
            continue;
        }

        if (p1 > 0) {
            std::cout << 2 << '\n';
            continue;
        }

        std::cout << -1 << '\n';
    }
}