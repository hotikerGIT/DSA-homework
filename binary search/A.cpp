#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> price(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> price[i];
    }
    std::sort(price.begin(), price.end());

    int q, m;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        std::cin >> m;

        int left = 0;
        int right = n - 1;
        int middle;

        while (left <= right) {
            middle = (left + right) / 2;

            if (price[middle] <= m) {
                left = middle + 1;
            }

            else {
                right = middle - 1;
            }
        }

        std::cout << left << std::endl;
    }
}