#include <iostream>
#include <vector>

signed main() {
    int n;
    std::cin >> n;
    std::vector<double> a(n);
    for (double& num : a) std::cin >> num;

    for (int i = 4; i < n; ++i) {
        bool flag = true;

        for (int j = i; j > i - 5; --j) {
            if (a[j] > 8.0) flag = false;
        }

        if (flag) {
            std::cout << i + 2;
            return 0;
        }
    }

    std::cout << 0;
}