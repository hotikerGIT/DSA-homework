#include <iostream>
#include <vector>
#include <unordered_set>

std::vector<int> parent;
std::vector<int> depth;

void dfs(const std::vector<std::vector<int>>& graph, int u, int prev, int d) {
    parent[u] = prev;
    depth[u] = d;

    for (int v : graph[u]) {
        if (v == prev) continue;
        dfs(graph, v, u, d + 1);
    }
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    depth.resize(n + 1);
    parent.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        std::cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    std::vector<int> bfs(n);
    std::vector<int> pos(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> bfs[i];
        pos[bfs[i]] = i;
    }
    if (bfs[0] != 1) {
        std::cout << "NO";
        return 0;
    }

    dfs(graph,  1, 0, 0);
    int cur = 0;
    for (int v : bfs) {
        int num = depth[v];
        if (num < cur) {
            std::cout << "No\n";
            return 0;
        }
        cur = num;
    }
    std::unordered_set<int> visited;
    int last_parent = 0;

    for (int v : bfs) {
        int cur_parent = parent[v];
        if (last_parent != cur_parent && visited.contains(cur_parent) || pos[last_parent] > pos[cur_parent]) {
            std::cout << "No\n";
            return 0;
        }

        last_parent = cur_parent;
        visited.insert(cur_parent);
    }

    std::cout << "Yes";
}