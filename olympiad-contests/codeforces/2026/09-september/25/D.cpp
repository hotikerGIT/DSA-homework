#include <iostream>
#include <vector>
#include <set>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    bool reversed_oddity = false;
    std::set<int> odd, even;

    for (int i = 1; i <= n; i++) {
        if (i % 2 == 0) even.insert(a[i - 1]);
        else odd.insert(a[i - 1]);
    }

    for (int i = 1; i <= n; ++i) {
        if ((n - i + 1) % 2 == 0) {
            if (!reversed_oddity && odd.contains(i) || reversed_oddity && even.contains(i))
                reversed_oddity = 1 - reversed_oddity;
        } else {
            if (!reversed_oddity && even.contains(i) || reversed_oddity && odd.contains(i)) {
                std::cout << "NO\n";
                return;
            }
        }
    }

    std::cout << "YES\n";
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}