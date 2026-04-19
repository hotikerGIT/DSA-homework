#include <algorithm>
#include <vector>
#include <iostream>
#define int long long

signed main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a.begin(), a.end());

    int ans = a.front();
    for (int i = 1; i < n; ++i) {
        int max_level = m / i;
        if (max_level == 0) break;

        int add_level = std::min(max_level, a[i] - a[i - 1]);
        ans += add_level;
        m -= add_level * i;
    }

    std::cout << (ans != a.front() ? ans : -1);
}