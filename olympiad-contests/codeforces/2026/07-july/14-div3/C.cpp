#include <iostream>
#include <vector>

int gcd(int a, int b) {
    if (a > b) std::swap(a, b);
    if (a == 0) return b;
    return gcd(a, b % a);
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        int n, x, y;
        std::cin >> n >> x >> y;
        std::vector<int> p(n);
        for (int i = 0; i < n; ++i) std::cin >> p[i];
        int g = gcd(x, y);

        bool flag = true;
        for (int i = 0; i < n; ++i) {
            int distance = p[i] - (i + 1);

            if (distance % g != 0) flag = false;
        }

        std::cout << (flag ? "Yes\n" : "No\n");
    }
}