#include <algorithm>
#include <vector>
#include <iostream>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        std::sort(a.begin(), a.end());
        std::vector<int> res;

        int left = 0, right = n - 1;
        while (left < right) {
            while (a[left] != 0 && a[right] != 0) {
                res.push_back(left + 1);
                res.push_back(right + 1);
                a[left]--;
                a[right]--;
            }

            while (left < right && a[left] == 0) left++;
            while (left < right && a[right] == 0) right--;
        }

        std::cout << res.size() / 2 << '\n';
        for (int i = 0; i < res.size(); i += 2) {
            std::cout << res[i] << ' ' << res[i + 1] << '\n';
        }
    }

    return 0;
}