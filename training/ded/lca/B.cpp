#include <iostream>
#include <vector>
#include <cmath>

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> parent(n + 1);

    for (int i = 2; i <= n; ++i) {

    }

    int log = std::log2(n) + 1;
    std::vector<std::vector<int>> bin_up(n + 1, std::vector<int>(log));
    for (int v = 1; v <= n; ++v) {
        bin_up[v].push_back()
    }
}