#include <iostream>
#include <vector>

std::vector<int> visited, stack, components;
std::vector<std::vector<int>> graph, rev_graph;
void dfs_sort(int cur) {
    visited[cur] = 1;

    for (int next : graph[cur]) {
        if (visited[next]) continue;
        dfs_sort(next);
    }

    stack.push_back(cur);
}

void dfs_mapping(int cur, int id) {
    components[cur] = id;

    for (int next : rev_graph[cur]) {
        if (components[next]) continue;
        dfs_mapping(next, id);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    visited.resize(n + 1);
    graph.resize(n + 1);
    rev_graph.resize(n + 1);
    components.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
    }

    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) dfs_sort(v);
    }

    int id = 1;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();

        if (components[v]) continue;
        dfs_mapping(v, id);
        ++id;
    }

    std::vector<std::vector<int>> condensed(id + 1);
    for (int v = 1; v <= n; ++v) {
        for (int u : graph[v]) {
            if (components[v] != components[u]) {
                condensed[components[v]].push_back(components[u]);
            }
        }
    }

    for (int v = 1; v <= n; ++v) {
        std::cout << components[v] << ' ';
    }
    std::cout << '\n';

    for (int v = 1; v < condensed.size(); ++v) {
        for (int u : condensed[v]) {
            std::cout << u << ' ';
        }
        std::cout << '\n';
    }
}