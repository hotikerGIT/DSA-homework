#include <iostream>
#include <vector>
#include <set>

std::vector<std::vector<int>> graph;
std::vector<int> enter, ret, visited;
std::set<int> good;
int t = 0;

void dfs(int cur, int prev) {
    t += 1;
    enter[cur] = t;
    ret[cur] = t;
    visited[cur] = true;
    int children = 0;

    for (int u : graph[cur]) {
        if (u == prev) continue;
        if (visited[u]) {
            ret[cur] = std::min(ret[cur], enter[u]);
            continue;
        }

        dfs(u, cur);
        children++;
        ret[cur] = std::min(ret[cur], ret[u]);

        if (prev != -1 && ret[u] >= enter[cur]) {
            good.insert(cur);
        }
    }

    if (prev == -1 && children > 1) {
        good.insert(cur);
    }
}

int main() {
    int n, m;
    std::cin >> n >> m;
    graph.resize(n + 1);
    enter.resize(n + 1);
    visited.resize(n + 1);
    ret.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    dfs(1, -1);

    std::cout << good.size() << '\n';
    for (int num : good) {
        std::cout << num << '\n';
    }
}