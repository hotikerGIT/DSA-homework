#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, h;
    std::cin >> n >> h;
    std::vector<int> sizes(n + 1);
    sizes[n] = 1;

    int ans = 0;
    int input = 0;

    for (int cur_size = n; cur_size >= 0 && h > 0; --cur_size) {
        for (int i = 0; i <= cur_size; ++i) {
            sizes[i] += input;
        }

        input = std::min(sizes[cur_size], h);
        h -= input;

        ans += input * (cur_size + 1);
    }

    std::cout << ans;
}