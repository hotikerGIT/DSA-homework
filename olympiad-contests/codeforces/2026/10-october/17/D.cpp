#include <iostream>
#include <vector>

void solve();

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n, m;
    std::cin >> n >> m;

    if (n == 1) {
        std::cout << 0 << '\n';
        return;
    }

    int k = (n + 1) / 2;

    std::vector<std::pair<int, int>> ans;

    for (int j = 1; j <= k; ++j) {
        int L0 = k - j + 1;
        int R0 = 2 * k - j;

        int r0 = std::min(R0, n - 1);

        if (L0 <= r0) {
            ans.emplace_back(L0 + 1, r0 + 1);
        }
    }

    std::cout << ans.size() << '\n';
    for (auto& [l, r] : ans) {
        std::cout << l << ' ' << r << '\n';
    }
}