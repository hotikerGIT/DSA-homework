#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) a[i] = 2 * (i + 1);

    int pow = -1;
    int x = n;
    while (x > 0) {
        pow++;
        x >>= 1;
    }

    std::vector<int> ans(n, 1);

    for (int bit = pow + 1; bit > 0; --bit) {
        int cnt = 0;
        for (int num : a) {
            cnt += (num >> bit) & 1;
        }

        if (cnt % 2 == 0) {
            int ind = (1 << (bit - 1)) - 1;
            ans[ind] = 0;
            a[ind] /= 2;
        }
    }

    for (int bit : ans) std::cout << bit << ' ';
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}