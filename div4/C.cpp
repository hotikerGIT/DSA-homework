#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        bool odd_flag = false;
        bool even_flag = false;

        for (int i = 0; i < n; i++) {
            std::cin >> a[i];

            if (a[i] % 2 == 0) {
                even_flag = true;
            }

            else {
                odd_flag = true;
            }
        }

        if (odd_flag && even_flag) {
            std::sort(a.begin(), a.end());
        }

        for (int num : a) {
            std::cout << num << " ";
        }
        std::cout << "\n";
    }
}