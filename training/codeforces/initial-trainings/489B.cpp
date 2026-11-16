#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

int main() {
    int n, m;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::cin >> m;
    std::vector<int> b(m);
    for (int i = 0; i < m; ++i) std::cin >> b[i];

    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int ans = 0;
    int left = 0;
    int right = 0;

    while (left < n && right < m) {
        if (std::abs(a[left] - b[right]) <= 1) {
            ans++;
            left++;
            right++;
            continue;
        }

        if (a[left] < b[right]) left++;
        else right++;
    }

    std::cout << ans;
}