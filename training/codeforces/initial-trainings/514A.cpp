#include <iostream>
#include <vector>
#define int long long

signed main() {
    int x;
    std::cin >> x;
    std::vector<int> res;

    while (x >= 10) {
        res.push_back(std::min(x % 10, 9 - (x % 10)));
        x /= 10;
    }

    if (x == 9) {
        std::cout << x;
    } else {
        std::cout << std::min(x, 9 - x);
    }

    for (int i = res.size() - 1; i >= 0; --i) std::cout << res[i];
}