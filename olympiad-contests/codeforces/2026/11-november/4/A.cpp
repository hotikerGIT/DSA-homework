#include <iostream>

void solve() {
    int l, r;
    std::cin >> l >> r;
    int sum = 0;
    for (int i = l; i <= r; ++i) {
        sum += i;
    }

    int ans = 0;
    while (std::abs(sum) > std::max(std::abs(l), std::abs(r))) {
        ans++;

        if (l >= 0) {
            sum -= r;
            r--;
        } else if (r <= 0) {
            sum -= l;
            ++l;
        } else {
            if (-l < r) {
                sum -= r;
                r--;
            } else {
                sum -= l;
                l++;
            }
        }
    }
    std::cout << ans << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}