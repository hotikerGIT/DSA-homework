#include <iostream>
#include <vector>
#include <algorithm>

int recursion(std::vector<int>& a, int cur_digit, std::vector<int>& digits) {
    int upper = *std::upper_bound(digits.begin(), digits.end(), a[cur_digit]);
    int lower = *std::upper_bound(digits.rbegin(), digits.rend(), a[cur_digit]);
    int middle = upper - 1;

    int res = std::min()
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int a, n;
        std::cin >> a >> n;
        std::vector<int> d(n);
        for (int i = 0; i < n; ++i) std::cin >> d[i];

        int log = 0;
        int a_cp = a;
        while (a > 0) {
            log++;
            a /= 10;
        }


    }
}