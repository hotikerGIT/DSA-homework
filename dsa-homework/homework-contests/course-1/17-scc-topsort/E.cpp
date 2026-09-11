#include <vector>
#include <map>
#include <functional>
#include <iostream>
#include <set>
#define int long long

struct Edge {
    int start, end;
    int weight = 0;
};

int get_task_weight(int w) {
    int left = 1, right = 2e5;

    while (left <= right) {
        int mid = (left + right) / 2;
        if (mid * (mid - 1) / 2 <= w) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    int k = right;
    return k * w - k * (k + 1) * (k - 1) / 6;
}

std::vector<int> find_components(std::vector<std::vector<Edge>>& graph) {
    int size = graph.size();
    std::vector<int> stack;
    stack.reserve(size);
    std::vector<int> visited(size, 0);
    std::vector<int> components(size, 0);
    std::vector<std::vector<Edge>> rev_graph(size);

    for (int v = 1; v < size; ++v) {
        for (const Edge& e : graph[v]) {
            rev_graph[e.end].emplace_back(e.end, e.start, e.weight);
        }
    }

    std::function<void(int)> dfs_sort = [&](int cur) {
        visited[cur] = 1;
        for (const Edge& e : graph[cur]) {
            if (!visited[e.end]) {
                dfs_sort(e.end);
            }
        }
        stack.push_back(cur);
    };

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;
        for (const Edge& e : rev_graph[cur]) {
            if (!components[e.end]) {
                dfs_scc(e.end, id);
            }
        }
    };

    for (int v = 1; v < size; ++v) {
        if (!visited[v]) {
            dfs_sort(v);
        }
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

struct ComponentInfo {
    int total_weight;
};

std::vector<ComponentInfo> get_component_info(std::vector<std::vector<Edge>>& graph, std::vector<int>& components, int component_count) {
    std::vector<ComponentInfo> res(component_count + 1);
    for (int v = 1; v < graph.size(); ++v) {
        for (auto& u : graph[v]) {
            if (components[v] != components[u.end]) continue;
            res[components[v]].total_weight += get_task_weight(u.weight);
        }
    }

    return res;
}

std::vector<std::vector<Edge>> get_condensation(std::vector<std::vector<Edge>>& graph, std::vector<int>& components, int component_count) {
    std::vector<std::vector<Edge>> condensed_graph(component_count + 1);

    for (int v = 1; v < graph.size(); ++v) {
        for (auto& u : graph[v]) {
            int cur = components[v];
            int next = components[u.end];
            if (cur == next) continue;
            condensed_graph[cur].emplace_back(cur, next);
        }
    }

    return condensed_graph;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<Edge>> graph(n + 1), rev_graph(n + 1);
    for (int i = 0; i < n; ++i) {
        int end;
        std::cin >> end;
        graph[i + 1].emplace_back(i + 1, end);
        rev_graph[end].emplace_back(end, i + 1);
    }
    auto component_id = find_components(graph);
    int id = 0;
    for (int i = 1; i <= n; ++i) {
        id = std::max(component_id[i], id);
    }

    if (id == 1) {
        std::cout << 0;
        return 0;
    }

    std::vector<int> roots, indegree(id + 1), neighbour_roots(id + 1), component_root(id + 1), represents(id + 1);
    for (int v = 1; v <= n; ++v) {
        represents[component_id[v]] = v;
    }

    auto condensed_graph = get_condensation(rev_graph, component_id, id);

    for (int cid = 1; cid <= id; ++cid) {
        for (auto& edge : condensed_graph[cid]) {
            indegree[edge.end]++;
        }
    }

    for (int cid = 1; cid <= id; ++cid) {
        if (!indegree[cid]) roots.push_back(cid);
    }

    for (int i = 0; i + 1 < roots.size(); ++i) {
        neighbour_roots[roots[i]] = roots[i + 1];
    }
    neighbour_roots[roots.back()] = roots[0];

    std::set<std::pair<int, int>> leaves;
    std::function<void(int, int)> dfs_leaves = [&](int cur, int root){
        bool flag = true;
        component_root[cur] = root;

        for (auto edge : condensed_graph[cur]) {
            flag = false;
            dfs_leaves(edge.end, root);
        }

        if (flag) leaves.insert({cur, root});
    };

    for (int root : roots) {
        dfs_leaves(root, neighbour_roots[root]);
    }

    std::cout << leaves.size() << '\n';

    for (auto& [cid, root] : leaves) {
        std::cout << represents[root] << ' ' << represents[cid] << '\n';
    }
}