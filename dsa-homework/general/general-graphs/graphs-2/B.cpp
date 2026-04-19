#include <iostream>
#include <vector>

std::vector<int> color;
std::vector<std::vector<int>> graph;
std::vector<int> parent;
int cycle_start = -1, cycle_end = -1;

bool dfs(int cur) {
    color[cur] = 1;

    for (int u : graph[cur]) {
        if (color[u] == 1) {
            cycle_start = u;
            cycle_end = cur;
            return true;
        }
        if (color[u] == 0) {
            parent[u] = cur;
            if (dfs(u)) return true;
        }
    }

    color[cur] = 2;
    return false;
}

int main() {
    freopen("cycle2.in", "r", stdin);
    freopen("cycle2.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;
    color.resize(n + 1);
    graph.resize(n + 1);
    parent.resize(n + 1, -1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
    }

    bool flag = false;
    for (int i = 1; i <= n && !flag; ++i) {
        if (color[i] == 0) {
            if (dfs(i)) flag = true;
        }
    }

    if (!flag) {
        std::cout << "NO";
    } else {
        std::cout << "YES" << '\n';

        std::vector<int> cycle;
        cycle.push_back(cycle_start);
        for (int v = cycle_end; v != cycle_start; v = parent[v]) {
            cycle.push_back(v);
        }

        for (int i = cycle.size() - 1; i >= 0; --i) {
            std::cout << cycle[i] << ' ';
        }
    }

    return 0;
}