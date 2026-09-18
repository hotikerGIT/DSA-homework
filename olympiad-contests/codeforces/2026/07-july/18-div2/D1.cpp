#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <bit>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n, q;
        std::cin >> n >> q;

        std::vector<int> a(n);
        std::vector<int> indexes(n);
        for (int i = 0; i < n; ++i) {
            std::cin >> a[i];
            indexes[i] = i;
        }

        std::stable_sort(indexes.begin(), indexes.end(), [&](int i, int j) {
            return a[i] < a[j];
        });

        int k = 0;
        for (int i = 0; i < n; ++i) {
            k = std::max(k, (int)std::bit_floor((unsigned)indexes[i] ^ i));
        }

        std::cout << k << '\n';
    }
}