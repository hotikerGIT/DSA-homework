#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;

    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    bool has_nuts_flag = false;
    long long res = 1;
    int left = -1;

    for (int right = 0; right < n; ++right) {
        if (a[right] == 0) {
            continue;
        }

        if (left != -1) {
            res *= right - left;
        }

        has_nuts_flag = true;
        left = right;
    }

    if (!has_nuts_flag) {
        std::cout << 0;
    }

    else {
        std::cout << res;
    }
}