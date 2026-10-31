#include <iostream>
#include <vector>
#include <set>
#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::set<int> more;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        int p;
        std::cin >> p;
        sum += p;
        a[i] = p;

        if (p > 1) more.insert(i);
    }

    if (more.empty()) {
        std::cout << -1 << std::endl;
        return;
    }

    if (more.size() == 1) {
        int index = *more.begin();

        if (index == 0 || index == n - 1) {
            std::cout << a[index] << std::endl;
            return;
        }
    }

    if (more.size() == 2) {
        int left = *more.begin();
        int right = *more.rbegin();

        if (left == 0 && right == n - 1) {
            std::cout << a[left] + a[right] - 1 << std::endl;
            return;
        }
    }

    std::cout << sum - 1 << std::endl;
}

signed main() {
    int t;
    std::cin >> t;
    while(t--) solve();
}