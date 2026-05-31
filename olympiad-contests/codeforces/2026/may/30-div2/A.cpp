#include <iostream>
#include <vector>
#include <map>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::map<int, int> counter;
        for (int i = 0; i < n; ++i) {
            int a;
            std::cin >> a;
            counter[a]++;
        }

        int passed = 0;
        int ans = 1e9;
        for (auto [point, amount] : counter) {
            ans = std::min(ans, std::max(passed, n - passed - amount));
            passed += amount;
        }

        std::cout << ans << '\n';
    }
}