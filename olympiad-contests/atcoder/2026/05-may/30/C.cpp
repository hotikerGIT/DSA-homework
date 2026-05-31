#include <iostream>
#include <algorithm>
#include <vector>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<int> a(n), b(m);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < m; ++i) std::cin >> b[i];
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());

    int cnt = 0;
    int first = a.size() - 1;
    int second = b.size() - 1;

    while (first >= 0 && second >= 0) {
        while (second >= 0 && b[second] > 2 * a[first]) second--;

        if (second >= 0) {
            second--;
            first--;
            cnt++;
        }
    }

    std::cout << cnt;
}