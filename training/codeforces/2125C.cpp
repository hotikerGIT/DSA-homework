#include <iostream>
#include <vector>
#define int long long

void solve() {
    int l, r;
    std::cin >> l >> r;

    auto get_cnt = [&](int div) -> int {
        int r_ = r - (r % div);
        int l_ = l % div == 0 ? l : l + (div - l % div);

        if (r_ < l_) return 0;
        if (r_ == l_) return  1;

        int len = r_ - l_;
        int cnt = len / div;
        return cnt + 1;
    };

    std::vector<int> primes = {2, 3, 5, 7};
    int ans = 0;
    for (int mask = 1; mask < 1 << primes.size(); ++mask) {
        int bit_cnt = 0;
        for (int j = 0; j < 4; ++j) {
            bit_cnt += (mask >> j) & 1;
        }

        int factor = 1;
        for (int j = 0; j < 4; ++j) {
            if ((mask >> j) & 1) factor *= primes[j];
        }

        int addition = get_cnt(factor);

        if (bit_cnt & 1) {
            ans += addition;
        } else {
            ans -= addition;
        }
    }

    std::cout << r - l + 1 - ans << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}