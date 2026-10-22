#include <iostream>
#include <vector>

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> a(n), cnt(n + 1);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }

    for (int i = 0; i < n; ++i) {
        if (cnt[i] <= 2 * (k - 1)) {
            std::cout << "NO\n";
            return;
        }

        if (cnt[i] == 2 * k - 1) {
            std::cout << "YES\n";
            return;
        }
    }

    std::cout << "NO\n";
    return;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}