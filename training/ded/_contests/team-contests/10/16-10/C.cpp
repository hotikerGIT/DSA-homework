#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    std::set<int> nums;
    int n, k;
    std::cin >> n >> k;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        nums.insert(a);
    }

    int res = 0;
    while (!nums.empty()) {
        int a = *nums.begin();
        int chain_size = 0;

        while (nums.contains(a)) {
            nums.erase(a);
            a *= k;
            chain_size++;
        }

        res += (chain_size + 1) / 2;
    }

    std::cout << res;
}