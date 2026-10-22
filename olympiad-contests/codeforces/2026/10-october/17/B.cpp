#include <iostream>
#include <string>
#include <set>
#include <vector>

void solve();

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    int ans = 0;
    for (int j = 30; j >= 0; --j) {
        bool all_ones = true;
        bool all_zeros = true;

        for (int num : a) {
            if (((num >> j) & 1) == 1) all_zeros = false;
            else all_ones = false;
        }

        if (all_ones) {
            ans |= 1 << j;
        }

        if (all_ones || all_zeros) continue;

        ans |= (1 << (j + 1)) - 1;
    }

    std::cout << ans << '\n';
}