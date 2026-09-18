#include <iostream>
#include <vector>
#define int long long

signed main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];

        bool flag = true;
        for (int i = 0; i < n - 1; ++i) {
            if (a[i] < i + 1) {
                flag = false;
                break;
            }
            a[i + 1] += a[i] - i - 1;
        }

        if (a[n - 1] < n) flag = false;

        std::cout << (flag ? "YES\n" : "NO\n");
    }
}