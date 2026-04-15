#include <iostream>
#include <cmath>
#include <algorithm>

#define int long long

int count_even_abs(int a, int b) {
    if (a > b) return 0;

    if (a >= 0) {
        int first_even = (a % 2 == 0) ? a : a + 1;
        if (first_even > b) return 0;
        return (b - first_even) / 2 + 1;
    }
    else if (b <= 0) {
        int first = (a % 2 == 0) ? a : a + 1;
        if (first > b) return 0;
        return (b - first) / 2 + 1;
    }
    else {
        return count_even_abs(a, -1) + count_even_abs(0, b);
    }
}

signed main() {
    int l, r, d, u;
    std::cin >> l >> r >> d >> u;

    int ans = 0;

    for (int x = l; x <= r; ++x) {
        int abs_x = std::abs(x);

        int red_low = std::max(d, -abs_x);
        int red_high = std::min(u, abs_x);

        if (red_low <= red_high) {
            int red_count = red_high - red_low + 1;
            if (abs_x % 2 == 0) {
                ans += red_count;
            }
        }

        int green_up_low = std::max(d, abs_x + 1);
        int green_up_high = u;
        ans += count_even_abs(green_up_low, green_up_high);

        int green_down_low = d;
        int green_down_high = std::min(u, -abs_x - 1);
        ans += count_even_abs(green_down_low, green_down_high);
    }

    std::cout << ans;

    return 0;
}