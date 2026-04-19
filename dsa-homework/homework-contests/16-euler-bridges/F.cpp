#include <iostream>
#include <vector>
#define int long long

std::vector<std::vector<int>> graph;
std::vector<int> visited, non_loop;

void dfs(int v) {
    visited[v] = true;
    for (int to : graph[v]) {
        if (!visited[to]) {
            dfs(to);
        }
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin >> n >> m;
    graph.resize(n + 1);
    non_loop.resize(n + 1);
    visited.resize(n + 1);

    int p = 0;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        if (a == b) {
            p++;
        } else {
            graph[b].push_back(a);
            non_loop[a]++;
            non_loop[b]++;
        }
    }

    int edge_edge = 0;
    int edge_loop = p * (m - p);
    int loop_loop = p * (p - 1) / 2;
    for (int v = 1; v <= n; ++v) {
        edge_edge += non_loop[v] * (non_loop[v] - 1) / 2;
    }

    bool flag = true;
    bool dfs_done = false;

    for (int v = 1; v <= n; ++v) {
        if (visited[v] || graph[v].empty()) continue;
        if (!dfs_done) {
            dfs(v);
            dfs_done = true;
        }
        else {
            flag = false;
        }
    }

    if (flag) {
        std::cout << edge_edge + edge_loop + loop_loop;
    } else {
        std::cout << 0;
    }
}