#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long

void solve() {
    int n; std::string s;
    std::cin >> n >> s;
    std::vector<int> improve(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        improve[i] = std::max(i, n - i - 1);

        if (s[i] == 'L') {
            sum += i;
            improve[i] -= i;
        } else {
            sum += n - i - 1;
            improve[i] -= n - i - 1;
        }
    }

    std::sort(improve.rbegin(), improve.rend());
    for (int num : improve) {
        sum += num;
        std::cout << sum << ' ';
    }
    std::cout << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}