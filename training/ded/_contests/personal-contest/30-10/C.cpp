#include <iostream>
#include <vector>

void solve(int ind) {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<int>> graph(n);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> visited(n);
    auto dfs = [&](int cur, auto&& self) -> void {
        if (visited[cur]) return;
        visited[cur] = 1;

        for (int next : graph[cur]) self(next, self);
    };
    dfs(0, dfs);

    if (visited.back()) std::cout << ind;
}

int main() {
    int n;
    std::cin >> n;

    int i = 1;
    while (i <= n) {
        solve(i);
        ++i;
    }
}