#include <iostream>
#include <vector>
#define int long long

void solve();

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = n - 1; i >= 0; --i) std::cin >> a[i];

    int cur = 0;
    for (int num : a) {
        if (cur <= num) {
            cur += 2 * (num - cur);
        } else {
            cur -= 2 * (cur - num);
        }
    }

    std::cout << cur / 2 << '\n';
}