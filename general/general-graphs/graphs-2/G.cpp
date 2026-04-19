#include <iostream>
#include <vector>
#include <cmath>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    while (T--) {
        int n, m;
        std::cin >> n >> m;

        std::vector<int> x(n + 1);
        for (int i = 1; i <= n; ++i) {
            std::cin >> x[i];
        }

        std::vector<int> start_cnt(n + 1), end_cnt(n + 1);
        std::vector<std::pair<int, int>> people(m);

        for (int i = 0; i < m; ++i) {
            int s, d;
            std::cin >> s >> d;
            people[i] = {s, d};
            start_cnt[s]++;
            end_cnt[d]++;
        }

        bool possible = true;
        for (int v = 1; v <= n; ++v) {
            if (start_cnt[v] != end_cnt[v]) {
                possible = false;
                break;
            }
        }

        if (!possible) {
            std::cout << "-1\n";
            continue;
        }

        int ans = 0;
        for (auto [s, d] : people) {
            ans += std::abs(x[s] - x[d]);
        }

        std::cout << ans << "\n";
    }

    return 0;
}