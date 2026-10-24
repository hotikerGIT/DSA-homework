#include <iostream>
#include <vector>
#define int long long

signed main() {
    int n, c;
    std::cin >> n >> c;
    std::vector<int> weight(n + 1), color(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> weight[i];
    for (int i = 1; i <= n; ++i) {
        int col;
        std::cin >> col;
        color[i] = col - 1;
    }

    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector dp_take(n + 1, std::vector((1 << c) + 1, 0));
    std::vector dp_skip(n + 1, std::vector((1 << c) + 1, 0));

    // for (int v = 1; v <= n; ++v) dp_take[v][1 << color[v]] = weight[v];

    int ans = 0;
    auto dfs = [&](this auto&& self, int cur, int prev) -> void {
        bool is_leaf = true;
        for (int next : graph[cur]) {
            if (next == prev) continue;
            is_leaf = false;

            self(next, cur);

            for (int mask = 0; mask < 1 << c; ++mask) {
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    int add_mask = mask ^ submask;
                    int tmp = submask;
                    std::swap(add_mask, submask);

                    if (add_mask >> color[cur] & 1) {
                        dp_take[cur][mask] = std::max((int)dp_take[cur][mask],
                        dp_take[cur][add_mask ^ (1 << color[cur])] +
                        dp_skip[next][submask] +
                        weight[cur]);
                    }

                    dp_skip[cur][mask] = std::max(dp_skip[cur][mask],
                        dp_skip[cur][add_mask] +
                        std::max(
                            dp_take[next][submask],
                            dp_skip[next][submask]
                        )
                    );

                    submask = tmp;
                }
            }
        }

        if (is_leaf) dp_take[cur][1 << color[cur]] = weight[cur];
    };

    dfs(1, 0);
    for (auto& row : dp_take) for (auto& x : row) ans = std::max(ans, (int)x);
    for (auto& row : dp_skip) for (auto& x : row) ans = std::max(ans, (int)x);
    std::cout << ans;
}