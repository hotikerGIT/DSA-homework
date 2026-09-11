#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include <queue>
#define int long long

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::unordered_map<int, std::vector<std::pair<int, int>>> graph;
    for (int i = 0; i < n - 1; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph[x].emplace_back(y, w);
        graph[y].emplace_back(x, w);
    }

    std::queue<std::pair<int, int>> q;
    q.emplace(1, 0);
    std::unordered_set<int> visited;
    int edge_sum = 0;
    int max_branch = 0;
    while (!q.empty()) {
        auto [v, d] = q.front();
        q.pop();
        if (visited.contains(v)) continue;
        visited.insert(v);

        max_branch = std::max(max_branch, d);
        for (auto& [u, w] : graph[v]) {
            q.emplace(u, d + w);
            if (!visited.contains(u)) edge_sum += w;
        }
    }

    std::cout << 2 * edge_sum - max_branch;
}