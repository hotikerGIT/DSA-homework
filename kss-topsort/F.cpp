#include <iostream>
#include <vector>
#include <set>

std::vector<std::set<int>> graph, rev_graph;
std::vector<int> color, stack, visited;
bool dfs_cycle(int cur) {
    color[cur] = 1;

    for (int u : graph[cur]) {
        if (color[u] == 2) continue;
        if (color[u] == 1) return true;
        if (dfs_cycle(u)) return true;
    }

    color[cur] = 2;
    return false;
}

void dfs_top_sort(int cur) {
    visited[cur] = 1;
    for (int u : graph[cur]) {
        if (!visited[u]) dfs_top_sort(u);
    }
    stack.push_back(cur);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<char> letters(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> letters[i];
    rev_graph.resize(n + 1);
    graph.resize(n + 1);
    color.resize(n + 1);
    visited.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].insert(b);
        rev_graph[b].insert(a);
    }

    // проверка петель
    for (int v = 1; v <= n; ++v) {
        for (int u : graph[v]) {
            if (u == v) {
                std::cout << -1;
                return 0;
            }
        }
    }

    // проверка циклов
    for (int v = 1; v <= n; ++v) {
        if (!color[v] && dfs_cycle(v)) {
            std::cout << -1;
            return 0;
        }
    }

    // больше способов набрать -1 нет, строим дп
    for (int v = 1; v <= n; ++v) {
        if (!visited[v]) dfs_top_sort(v);
    }

    auto s = stack;
    int ans = 0;
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(26));
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();

        for (int c = 0; c < 26; ++c) {
            for (int u : rev_graph[v]) {
                dp[v][c] = std::max(dp[v][c], dp[u][c]);
            }
        }

        dp[v][letters[v] - 'a']++;
        ans = std::max(ans, dp[v][letters[v] - 'a']);
    }

    std::cout << ans;
}