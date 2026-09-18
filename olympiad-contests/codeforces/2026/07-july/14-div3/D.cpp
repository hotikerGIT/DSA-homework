#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

signed main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n, m;
        std::cin >> n >> m;
        std::vector<int> a(n), b(m + 1);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        for (int i = 1; i <= m; ++i) std::cin >> b[i];
        std::sort(b.begin(), b.end());

        int answer = 0;
        int cur = 0;
        for (int i = 0; i < m; ++i) {
            int diff = b[i + 1] - b[i];

            int sum = 0;
            for (int j = cur; j < cur + diff; ++j) {
                sum += a[j];
            }
            answer += std::abs(sum);
            cur += diff;
        }

        for (int j = cur; j < n; ++j) {
            answer += a[j];
        }

        std::cout << answer << '\n';
    }
}