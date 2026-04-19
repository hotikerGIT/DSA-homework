#include <iostream>
#include <vector>
#include <functional>
#define int long long

int MOD = 1e9 + 7;

struct Edge {
    int start, end;
    int weight = 0;

    Edge reverse() const {
        return {end, start, weight};
    }
};

std::vector<int> find_components(std::vector<std::vector<Edge>>& graph) {
    int size = graph.size();
    std::vector<int> stack, visited(size), components(size);
    std::vector<std::vector<Edge>> rev_graph(size);
    for (int v = 1; v < size; ++v) {
        for (Edge& u : graph[v]) {
            rev_graph[u.end].emplace_back(u.reverse());
        }
    }

    std::function<void(int)> dfs_sort = [&](int cur) {
        visited[cur] = 1;

        for (Edge& u : graph[cur]) {
            if (visited[u.end]) continue;
            dfs_sort(u.end);
        }

        stack.push_back(cur);
    };

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;

        for (auto& u : rev_graph[cur]) {
            if (components[u.end]) continue;
            dfs_scc(u.end, id);
        }
    }
    ;
    for (int v = 1; v < size; ++v) {
        if (visited[v]) continue;
        dfs_sort(v);
    }
    int id = 1;
    while (!stack.empty()) {
        int v = stack.back();
        stack.pop_back();
        if (!components[v]) {
            dfs_scc(v, id);
            id++;
        }
    }

    return components;
}

signed main() {
    int n, m;
    std::cin >> n;
    std::vector<std::vector<Edge>> graph(n + 1);
    std::vector<int> cost(n + 1);
    for (int i = 1; i <= n; ++i) {
        std::cin >> cost[i];
    }

    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].emplace_back(a, b);
    }

    auto components = find_components(graph);
    int id = 0;
    for (int cid : components) {
        id = std::max(cid, id);
    }

    std::vector<int> component_min(id + 1, 1e9), component_size(id + 1);
    for (int v = 1; v <= n; ++v) {
        int v_id = components[v];
        component_min[v_id] = std::min(component_min[v_id], cost[v]);
    }
    for (int v = 1; v <= n; ++v) {
        int v_id = components[v];
        component_size[v_id] += cost[v] == component_min[v_id];
    }

    int ans1 = 0;
    int ans2 = 1;
    for (int i = 1; i <= id; ++i) {
        ans1 += component_min[i];
        ans2 = (ans2 * component_size[i]) % MOD;
    }

    std::cout << ans1 << ' ' << ans2;
}