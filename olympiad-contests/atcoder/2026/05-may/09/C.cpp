#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, k;
    std::cin >> n >> k;
    k--;
    std::vector<std::vector<int>> grid(n);
    for (int i = 0; i < n; ++i) {
        int length;
        std::cin >> length;
        grid[i].resize(length);

        for (int j = 0; j < length; ++j) {
            std::cin >> grid[i][j];
        }
    }

    std::vector<int> c(n);
    for (int i = 0; i < n; ++i) std::cin >> c[i];

    for (int i = 0; i < n; ++i) {
        int skip = c[i] * grid[i].size();

        if (k >= skip) {
            k -= skip;
        } else {
            std::cout << grid[i][k % grid[i].size()];
            break;
        }
    }
}