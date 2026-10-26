#include <iostream>
#include <vector>
#include <set>
#include <functional>
#define int long long

struct Edge {
    int start, end, index;
    bool is_bridge = false;
};

std::vector<std::vector<Edge>> graph;
std::vector<int> enter, ret, visited;
int t = 0;

void find_bridges(int cur, int prev) {
    t += 1;
    enter[cur] = t;
    ret[cur] = t;
    visited[cur] = true;

    for (auto& edge : graph[cur]) {
        int u = edge.end;
        if (u == prev) continue;
        if (visited[u]) {
            ret[cur] = std::min(ret[cur], enter[u]);
            continue;
        }

        find_bridges(u, cur);
        ret[cur] = std::min(ret[cur], ret[u]);

        if (ret[u] > enter[cur]) {
            edge.is_bridge = true;
        }
    }
}

std::vector<int> find_components() {
    int size = graph.size();
    std::vector<int> components(size, 0);

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;

        for (const Edge& e : graph[cur]) {
            if (!e.is_bridge && !components[e.end]) {
                dfs_scc(e.end, id);
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
        for (auto& u : graph[v]) {
            int cur = components[v];
            int next = components[u.end];
            if (cur == next) continue;
            condensed_graph[cur].push_back(next);
        }
    }

    return condensed_graph;
}

void solve() {
    graph.clear();
    enter.clear();
    visited.clear();
    ret.clear();
    t = 0;

    int n, m;
    std::cin >> n >> m;

    graph.resize(n + 1);
    enter.resize(n + 1);
    visited.resize(n + 1);
    ret.resize(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[b].emplace_back(b, a, i + 1, 0);
        graph[a].emplace_back(a, b, i + 1, 0);
    }
    find_bridges(1, -1);

    std::set<int> bridges;
    for (int v = 1; v <= n; ++v) {
        for (auto& edge : graph[v]) {
            if (edge.is_bridge) bridges.insert(edge.index);
        }
    }

    for (int v = 1; v <= n; ++v) {
        for (auto& edge : graph[v]) {
            if (bridges.contains(edge.index)) edge.is_bridge = true;
        }
    }

    auto components = find_components();
    int max_id = 1;
    for (int cid : components) max_id = std::max(max_id, cid);
    auto tree = get_condensation(components, max_id);

    std::vector<int> visit(n + 1);
    std::vector<int> comp_size(max_id + 1, 0);
    auto find_comp_size = [&](int cur, auto&& self) -> int {
        if (visit[cur]) return 0;
        visit[cur] = 1;

        int ans = 1;
        for (auto& e : graph[cur]) {
            if (components[e.end] == components[e.start]) {
                ans += self(e.end, self);
            }
        }

        return ans;
    };

    for (int v = 1; v <= n; ++v) {
        int cid = components[v];
        if (!comp_size[cid]) {
            comp_size[cid] = find_comp_size(v, find_comp_size);
        }
    }

    int ans = 0;
    auto dfs_ans = [&](int cur, int prev, auto&& self) -> int {
        int subtree_size = comp_size[cur];

        for (int next : tree[cur]) {
            if (next != prev) {
                subtree_size += self(next, cur, self);;
            }
        }

        ans = std::max(subtree_size * (n - subtree_size), ans);
        return subtree_size;
    };
    dfs_ans(1, 0, dfs_ans);

    std::cout << n * (n - 1) / 2 - ans << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int test;
    std::cin >> test;
    while(test--) solve();
}