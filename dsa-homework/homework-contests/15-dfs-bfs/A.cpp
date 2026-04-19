#include <iostream>
#include <vector>
#include <unordered_map>

void dfs(std::vector<std::vector<int>>& map, std::vector<std::pair<int, int>>& intervals, int v, int parent, int& time) {
    //std::cout << "(" << v << ")" << std::endl;
    intervals[v + 1].first = time++;

    for (int u : map[v]) {
        if (u == parent) continue;
        dfs(map, intervals, u, v, time);
    }

    intervals[v + 1].second = time;
}

int main() {
    freopen("ancestor.in", "r", stdin);
    freopen("ancestor.out", "w", stdout);


    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n);
    int start = -1;
    for (int i = 0; i < n; ++i) {
        int u;
        std::cin >> u;

        if (u == 0) {
            start = i;
            continue;
        }
        u--;

        graph[u].push_back(i);
        graph[i].push_back(u);
    }

    std::vector<std::pair<int, int>> intervals(n + 1);
    int time = 0;
    dfs(graph, intervals, start, -1, time);

    /*for (int i = 0; i < n; ++i) {
        std::cout << intervals[i].first << ' ' << intervals[i].second << '\n';
    }*/

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        std::cout << (intervals[a].first <= intervals[b].first && intervals[b].second <= intervals[a].second) << '\n';
    }
}