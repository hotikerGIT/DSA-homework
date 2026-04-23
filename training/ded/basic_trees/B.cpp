#include <iostream>
#include <vector>

std::vector<std::vector<int>> graph;
std::vector<int> sizes;

void dfs(int cur, int prev) {
    sizes[cur] = 1;

    for (int next : graph[cur]) {
        if (next == prev) continue;
        dfs(next, cur);
        sizes[cur] += sizes[next];
    }
}

int main() {
    int n;
    std::cin >> n;
    graph.resize(n + 1);
    sizes.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, -1);
    for (int i = 1; i <= n; ++i) {
        std::cout << sizes[i] << ' ';
    }
}