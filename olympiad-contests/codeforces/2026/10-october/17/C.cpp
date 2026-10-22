#include <iostream>
#include <string>
#include <set>
#include <vector>
#define int long long

void solve();

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void win() {
    std::cout << "moggity\n";
}

void loose() {
    std::cout << "larpity\n";
}

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int sum = 0;
    int even_cnt = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum += a[i];
        even_cnt += a[i] % 2 == 0;
    }

    if (sum % 2 == 0) {
        win();
        return;
    }

    if (n == 2) {
        loose();
        return;
    }

    if (even_cnt > 0) {
        win();
        return;
    }

    if (n == 3) {
        loose();
        return;
    }

    win();
}