#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        sum += a[i];
    }

    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p;
        std::cin >> p;
        graph[i].push_back(p);
        graph[p].push_back(i);
    }

    int ans = -1e18;
    auto dfs = [&](int cur, int prev, auto&& self) -> std::pair<int, int> {
        int sub_cnt = 1;
        int sub_sum = a[cur - 1];
        int total = 0;

        for (int next : graph[cur]) {
            if (next != prev) {
                auto [cnt, sm] = self(next, cur, self);

                sub_cnt += cnt;
                sub_sum += sm;

                total += cnt * sm;
            }
        }

        ans = std::max(ans, total + (n - sub_cnt) * (sum - sub_sum));
        return {sub_cnt, sub_sum};
    };
    dfs(1, 0, dfs);
    std::cout << ans;
}