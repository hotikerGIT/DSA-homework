#include <iostream>
#include <vector>
#include <set>
#define int long long


void solve() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    std::multiset<int> odd, even;

    for (int i = 0; i < n; ++i) {
        if (a[i] < 0) {
            if ((i + 1) % 2 == 0) {
                odd.insert(-a[i]);
                even.insert(a[i]);
            } else {
                even.insert(-a[i]);
                odd.insert(a[i]);
            }
        } else {
            if ((i + 1) % 2 == 0) {
                even.insert(a[i]);
                odd.insert(-a[i]);
            } else {
                odd.insert(a[i]);
                even.insert(-a[i]);
            }
        }
    }

    int even_cnt = n / 2;
    int odd_cnt = n - even_cnt;

    int sum = 0;

    for (int i = 0; i < even_cnt; ++i) {
        auto it = even.end();
        --it;
        sum += *it;
        even.erase(it);
    }

    for (int i = 0; i < odd_cnt; ++i) {
        auto it = odd.end();
        --it;
        sum += *it;
        odd.erase(it);
    }

    std::cout << sum << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
    return 0;
}