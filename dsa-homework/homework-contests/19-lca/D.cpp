#include <iostream>
#include <vector>
#include <cmath>
#include <set>
#include <functional>

std::vector<int> euler, depth;
std::vector<std::vector<int>> graph;
std::vector<int> enter, ret, visited;
std::set<std::pair<int, int>> bridges;
int t = 0;

std::vector<int> find_components() {
    int size = graph.size();
    std::vector<int> components(size, 0);

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;
        for (int next : graph[cur]) {
            if (!components[next] && !bridges.contains({next, cur}) && !bridges.contains({cur, next})) {
                dfs_scc(next, id);
            }
        }
    };

    int id = 1;
    for (int v = 1; v < size; ++v) {
        if (!components[v]) {
            dfs_scc(v, id);
            ++id;
        }
    }

    return components;
}

std::vector<std::vector<int>> get_condensation(std::vector<int>& components, int component_count) {
    std::vector<std::vector<int>> condensed_graph(component_count + 1);

    for (int v = 1; v < graph.size(); ++v) {
        for (int u : graph[v]) {
            int cur = components[v];
            int next = components[u];
            if (cur == next) continue;
            condensed_graph[cur].push_back(next);
        }
    }

    return condensed_graph;
}

void dfs_bridges(int cur, int prev) {
    t += 1;
    enter[cur] = t;
    ret[cur] = t;
    visited[cur] = true;

    for (int u : graph[cur]) {
        if (u == prev) continue;
        if (visited[u]) {
            ret[cur] = std::min(ret[cur], enter[u]);
            continue;
        }

        dfs_bridges(u, cur);
        ret[cur] = std::min(ret[cur], ret[u]);

        if (ret[u] > enter[cur]) {
            bridges.insert({u, cur});
            bridges.insert({cur, u});
        }
    }
}

void dfs_euler(int cur, int prev, std::vector<std::vector<int>>& cond_graph) {
    euler.push_back(cur);

    for (int next : cond_graph[cur]) {
        if (next == prev) continue;
        depth[next] = depth[cur] + 1;
        dfs_euler(next, cur, cond_graph);
        euler.push_back(cur);
    }
}

signed main() {
    freopen("magic.in", "r", stdin);
    freopen("magic.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, f;
    std::cin >> n >> m >> f;
    graph.resize(n + 1);
    enter.resize(n + 1);
    visited.resize(n + 1);
    ret.resize(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[b].push_back(a);
        graph[a].push_back(b);
    }
    dfs_bridges(1, -1);

    auto components = find_components();
    int id = 0;
    for (auto cid : components) id = std::max(id, cid);
    auto condensed_graph = get_condensation(components, id);

    depth.resize(id + 1);
    dfs_euler(components[f], -1, condensed_graph);
    int log = std::log2(euler.size()) + 1;

    std::vector<std::vector<int>> sparse_table(log, std::vector<int>(euler.size()));
    for (int i = 0; i < euler.size(); ++i) {
        sparse_table[0][i] = euler[i];
    }

    auto comp = [&](int a, int b) { return depth[a] < depth[b]; };

    for (int power = 1; power < log; ++power) {
        for (int index = 0; index + (1 << power) <= euler.size(); ++index) {
            sparse_table[power][index] = std::min(
                    sparse_table[power - 1][index],
                    sparse_table[power - 1][index + (1 << (power - 1))],
                    comp
            );
        }
    }

    std::vector<std::pair<int, int>> vertices(id + 1, {1e9, -1});
    for (int i = 0; i < euler.size(); ++i) {
        auto& v = vertices[euler[i]];
        v.first = std::min(i, v.first);
        v.second = std::max(i, v.second);
    }

    auto LCA = [&](int a, int b) {
        if (a == b) return a;
        int left = vertices[a].first;
        int right = vertices[b].second;
        if (left > right) std::swap(left, right);

        int length = right - left + 1;
        int k = std::log2(length);

        int candidate1 = sparse_table[k][left];
        int candidate2 = sparse_table[k][right - (1 << k) + 1];

        return std::min(candidate1, candidate2, comp);
    };

    int k;
    std::cin >> k;
    for (int i = 0; i < k; ++i) {
        int a, b;
        std::cin >> a >> b;

        std::cout << depth[LCA(components[a], components[b])] << '\n';
    }
}