#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> p(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> p[i];
    std::vector<int> indexes(n + 1);
    for (int i = 1; i <= n; ++i) {
        indexes[p[i]] = i;
    }

    std::vector<int> pref_max(n + 1), suf_min(n + 1, 2e9);
    for (int i = 0; i < n; ++i) {
        pref_max[i + 1] = std::max(pref_max[i], indexes[i + 1]);
        suf_min[n - i - 1] = std::min(suf_min[n - i], indexes[n - i]);
    }

    int k = 0;
    for (; k < n; ++k) {
        if (pref_max[k + 1] >= suf_min[n - (k + 1)]) break;
    }

    std::cout << (k ? k : -1);
}