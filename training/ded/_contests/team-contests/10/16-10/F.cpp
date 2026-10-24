#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int prod = 1;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    for (int i = 0; i < n; ++i) {
        prod = std::max(prod, 1);

        prod = prod * (1 + a[i] / 10000);
    }
}