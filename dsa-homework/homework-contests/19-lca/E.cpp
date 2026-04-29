#include <iostream>
#include <vector>
#include <cmath>
#define int long long

std::vector<int> euler, depth;
std::vector<std::vector<int>> graph;

void dfs(int cur, int prev) {
    euler.push_back(cur);

    for (int next : graph[cur]) {
        if (next == prev) continue;
        depth[next] = depth[cur] + 1;
        dfs(next, cur);
        euler.push_back(cur);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    graph.resize(n + 1);
    depth.resize(n + 1);
    for (int i = 2; i <= n; ++i) {
        int p;
        std::cin >> p;
        graph[p].push_back(i);
    }
    dfs(1, -1);
    int log = std::log2(euler.size()) + 1;

    std::vector<std::vector<int>> sparse_table(log, std::vector<int>(euler.size()));
    for (int i = 0; i < euler.size(); ++i) {
        sparse_table[0][i] = euler[i];
    }

    auto comp = [&](int a, int b) { return depth[a] < depth[b]; };

    for (int power = 1; power < log; ++power) {
        for (int index = 0; index + (1 << power) <= euler.size(); ++index) {
            sparse_table[power][index] = std::min(
                    sparse_table[power - 1][index],
                    sparse_table[power - 1][index + (1 << (power - 1))],
                    comp
            );
        }
    }

    std::vector<std::pair<int, int>> vertices(n + 1, {1e9, -1});
    for (int i = 0; i < euler.size(); ++i) {
        auto& v = vertices[euler[i]];
        v.first = std::min(i, v.first);
        v.second = std::max(i, v.second);
    }

    auto LCA = [&](int a, int b) {
        if (a == b) return a;
        int left = vertices[a].first;
        int right = vertices[b].second;
        if (left > right) std::swap(left, right);

        int length = right - left + 1;
        int k = std::log2(length);

        int candidate1 = sparse_table[k][left];
        int candidate2 = sparse_table[k][right - (1 << k) + 1];

        return std::min(candidate1, candidate2, comp);
    };

    for (int i = 0; i < q; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;

        int lca = 1;
        lca = std::max(lca, LCA(a, b), comp);
        lca = std::max(lca, LCA(a, c), comp);
        lca = std::max(lca, LCA(b, c), comp);

        int ans = 0;
        auto get_dist = [&](int a, int b) {
            return depth[a] + depth[b] - 2 * depth[LCA(a, b)] + 1;
        };

        ans = std::max(ans, get_dist(lca, a));
        ans = std::max(ans, get_dist(lca, b));
        ans = std::max(ans, get_dist(lca, c));

        std::cout << ans << '\n';
    }
}