#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define int long long

int gcd(int a, int b) {
    if (a < b) std::swap(a, b);
    if (b == 0) return a;
    a %= b;
    return gcd(a, b);
}

bool bad(const std::vector<int>& a) {
    std::set<int> check(a.begin(), a.end());
    return a.size() > 1 && check.size() > 1 && check.size() < a.size();
}


signed main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::sort(a.begin(), a.end());

    std::vector<int> diff(n - 1);
    int gcd_all = 0;

    for (int i = 1; i < n; ++i) {
        diff[i - 1] = a[i] - a[i - 1];
        gcd_all = gcd(gcd_all, diff[i - 1]);
    }

    std::set<int> check(diff.begin(), diff.end());

    if (bad(a)) {
        std::cout << -1;
        return 0;
    }

    if (check.size() == 1) {
        std::cout << 0;
        return 0;
    }


    int res = 0;
    for (int num : diff) {
        res += num / gcd_all - 1;
    }

    std::cout << res;
}