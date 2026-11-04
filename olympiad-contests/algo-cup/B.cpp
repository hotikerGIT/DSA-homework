#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1), rev_graph(n + 1);
    std::vector<int> out_degree(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
        out_degree[a]++;
    }

    int root = 0;
    for (int v = 1; v <= n; ++v) {
        if (out_degree[v] == 0) {
            root = v;
            break;
        }
    }

    int ans = 0;
    auto dfs = [&](int cur, int prev, bool on_path, auto&& self) -> void {
        for (int next : rev_graph[cur]) {
            if (next != prev) {
                self(next, cur, false, self);
            }
        }

        int next_cnt = -on_path;
        for (int next : graph[cur]) {
            if (next != prev) {
                next_cnt++;
                self(next, cur, true, self);
            }
        }

        ans += (next_cnt + 1) / 2;
    };

    dfs(root, 0, false, dfs);
    std::cout << ans << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}