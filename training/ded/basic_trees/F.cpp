#include <iostream>
#include <vector>
#include <map>

std::vector<std::vector<int>> ass_graph, graph, rev_graph;
std::vector<std::map<int, int>> vertices;
std::vector<int> needed;
void dfs(int cur, int prev) {
    if (needed[cur] != -1) return;

    bool is_leaf = true;
    for (int next : ass_graph[cur]) {
        if (next == prev) continue;
        is_leaf = false;
    } if (is_leaf) {
        needed[cur] = 0;
        return;
    }

    for (int next : graph[cur]) {
        if (next == prev) continue;
        dfs(next, cur);
        vertices[cur][next] = needed[next];
    }

    for (int next : rev_graph[cur]) {
        if (next == prev) continue;
        dfs(next, cur);
        vertices[cur][next] = needed[next] + 1;
    }
}

int main() {
    int n;
    std::cin >> n;
    graph.resize(n + 1);
    rev_graph.resize(n + 1);
    ass_graph.resize(n + 1);
    needed.resize(n + 1, -1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        rev_graph[b].push_back(a);
        ass_graph[a].push_back(b);
        ass_graph[b].push_back(a);
    }

    vertices.resize(n + 1);
    dfs(1, -1);
    int min = 1e9;
    std::vector<int> res;
    for (int v = 1; v <= n; ++v) {
        if (needed[v] < min) {
            min = needed[v];
            res.clear();
        }

        if (needed[v] == min) {
            res.push_back(v);
        }
    }

    std::cout << min << '\n';
    for (int num : res) {
        std::cout << num << ' ';
    }
}