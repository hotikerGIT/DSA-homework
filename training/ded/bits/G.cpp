#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> basis;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        for (int b : basis) {
            a = std::min(a, a ^ b);
        }
        if (a > 0) basis.push_back(a);
    }
    std::sort(basis.begin(), basis.end(), std::greater<>());
    int result = 0;
    for (int b : basis) {
        result = std::max(result, result ^ b);
    }
    std::cout << result;
}