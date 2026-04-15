#include <vector>
#include <functional>
#define int long long

std::vector<int> find_components(std::vector<std::vector<int>>& graph) {
    int size = graph.size();
    std::vector<int> stack, visited(size), components(size);
    std::vector<std::vector<int>> rev_graph(size);
    for (int v = 1; v < size; ++v) {
        for (int u : graph[v]) {
            rev_graph[u].push_back(v);
        }
    }

    std::function<void(int)> dfs_sort = [&](int cur) {
        visited[cur] = 1;

        for (int u : graph[cur]) {
            if (visited[u]) continue;
            dfs_sort(u);
        }

        stack.push_back(cur);
    };

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;

        for (auto u : rev_graph[cur]) {
            if (components[u]) continue;
            dfs_scc(u, id);
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
            rev_graph[u.start].emplace_back(u.reverse());
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