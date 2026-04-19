#include <vector>
#include <map>
#include <functional>
#include <iostream>
#define int long long

struct Edge {
    int start, end;
    int weight = 0;
};

std::vector<int> subtracts = { 1 };
std::vector<int> prefix;


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

    std::vector<std::vector<std::pair<int, int>>> temp(component_count + 1);

    for (int v = 1; v < graph.size(); ++v) {
        for (auto& u : graph[v]) {
            int cur = components[v];
            int next = components[u.end];
            if (cur == next) continue;
            temp[cur].emplace_back(next, u.weight);
        }
    }

    for (int i = 1; i <= component_count; ++i) {
        if (temp[i].empty()) continue;

        std::sort(temp[i].begin(), temp[i].end(), [](auto& a, auto& b) {
            if (a.first != b.first) return a.first < b.first;
            return a.second > b.second;
        });

        for (size_t j = 0; j < temp[i].size(); ++j) {
            if (j > 0 && temp[i][j].first == temp[i][j-1].first) continue;
            condensed_graph[i].emplace_back(i, temp[i][j].first, temp[i][j].second);
        }
    }

    return condensed_graph;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    std::vector<std::vector<Edge>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int x, y, w;
        std::cin >> x >> y >> w;
        graph[x].emplace_back(x, y, w);
    }
    auto component_id = find_components(graph);
    int id = 0;
    for (auto cid : component_id) {
        id = std::max(id, cid);
    }

    auto component_info = get_component_info(graph, component_id, id);
    auto condensed_graph = get_condensation(graph, component_id, id);

    int s;
    std::cin >> s;
    int start = component_id[s];
    std::vector<int> dp(id + 1);
    dp[start] = component_info[start].total_weight;
    std::function<void(int)> dfs = [&](int cur) {
        for (auto& edge : condensed_graph[cur]) {
            int u = edge.end;
            int new_val = component_info[u].total_weight + edge.weight + dp[cur];

            if (new_val > dp[u]) {
                dp[u] = new_val;
                dfs(u);
            }
        }
    };
    dfs(start);

    int ans = 0;
    for (int num : dp) {
        ans = std::max(ans, num);
    }
    std::cout << ans;
}