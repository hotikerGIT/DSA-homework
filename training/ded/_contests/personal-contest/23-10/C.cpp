#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;

    int left = 1;
    int right = 1e18;
    int ans = 0;

    auto log_ten = [&](int num) {
        int res = 0;
        while (num > 0) {
            res++;
            num /= 10;
        }
        return res - 1;
    };

    auto raise = [&](int power) {
        int prod = 1;

        for (int i = 0; i < power; ++i) {
            prod *= 10;
        }

        return prod;
    };

    auto func = [&](int l, int r) {
        int ten_l = log_ten(l);
        int ten_r = log_ten(r);

        int res = 0;
        if (ten_l == ten_r) {
            res = (r - l + 1) * (ten_l + 1);
        } else {
            res = (raise(ten_l + 1) - l) * (ten_l + 1) +
                (r - raise(ten_r) + 1) * (ten_r + 1);
        }

        for (int i = ten_l + 1; i < ten_r; ++i) {
            res += (raise(i + 1) - raise(i)) * (i + 1);
        }

        return res;
    };

    while (left <= right) {
        int mid = (left + right) / 2;

        if (func(mid, mid + n - 1) >= k) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }

    if (func(ans, ans + n - 1) == k) {
        std::cout << ans;
    } else {
        std::cout << -1;
    }
}