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

    std::vector dp_take(n + 1, std::vector(1 << c, (int)-1e18));
    std::vector dp_skip(n + 1, std::vector(1 << c, (int)-1e18));

    for (int v = 1; v <= n; ++v) dp_take[v][1 << color[v]] = weight[v];

    int ans = 0;
    auto dfs = [&](int cur, int prev, auto&& self) -> void {
        dp_skip[cur][0] = 0;

        for (int next : graph[cur]) {
            if (next == prev) continue;

            self(next, cur, self);

            for (int mask = (1 << c) - 1; mask >= 0; --mask) {
                for (int submask = mask; submask > 0; submask = (submask - 1) & mask) {
                    int add_mask = mask ^ submask;

                    if (add_mask >> color[cur] & 1) {
                        dp_take[cur][mask] = std::max((int)dp_take[cur][mask],
                                                      dp_take[cur][add_mask] +
                                                      dp_skip[next][submask]);
                    }

                    dp_skip[cur][mask] = std::max(dp_skip[cur][mask],
                                                  dp_skip[cur][add_mask] + std::max(
                                                          dp_take[next][submask],
                                                          dp_skip[next][submask])
                    );
                }
            }
        }
    };

    dfs(1, 0, dfs);
    for (auto& row : dp_take) for (auto& x : row) ans = std::max(ans, (int)x);
    for (auto& row : dp_skip) for (auto& x : row) ans = std::max(ans, (int)x);
    std::cout << ans;
}