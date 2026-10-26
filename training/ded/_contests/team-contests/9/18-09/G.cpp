#include <iostream>
#define int long long

signed main() {
    int a, b, c, d;
    std::cin >> a >> b >> c >> d;

    if (c < d) {
        std::swap(a, b);
        std::swap(c, d);
    }

    if (c != d && a < b) {
        std::cout << 0;
        return 0;
    }

    int all_diff = c - d;
    int r = a - b;

    if (r != 0 && all_diff % r != 0) {
        std::cout << 0;
        return 0;
    }

    if (all_diff == 0) {
        if (r != 0) {
            std::cout << c;
            return 0;
        }

        int res = 0;
        res += c / ((2 * a) + 1);
        c %= 2 * a + 1;
        res += c / (a + 1);
        c %= a + 1;
        res += c;

        std::cout << res;
        return 0;
    }

    if (r == 0) {
        std::cout << 0;
        return 0;
    }

    int priz_pob = all_diff / r;
    int priz = priz_pob % 2;
    int pob = priz_pob / 2;

    int c_almost = pob * (2 * a + 1) + priz * (a + 1);
    int d_almost = pob * (2 * b + 1) + priz * (b + 1);

    if (c_almost > c || d_almost > d) {
        std::cout << 0;
        return 0;
    }

    std::cout << (c - c_almost) + priz + pob;
}