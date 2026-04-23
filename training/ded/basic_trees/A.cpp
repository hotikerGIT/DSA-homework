#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<int> depths;

void dfs(int cur, int prev) {
    for (int next : graph[cur]) {
        if (next == prev) continue;
        depths[next] = depths[cur] + 1;
        dfs(next, cur);
    }
}

int main() {
    int n;
    std::cin >> n;
    graph.resize(n + 1);
    depths.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; ++i) {
        std::cout << depths[i] << ' ';
    }
}