#include <iostream>
#include <vector>
#include <set>
#include <functional>

std::vector<int> find_components(std::vector<std::vector<int>>& graph) {
    int size = graph.size();
    std::vector<int> stack;
    stack.reserve(size);
    std::vector<int> visited(size, 0);
    std::vector<int> components(size, 0);
    std::vector<std::vector<int>> rev_graph(size);

    for (int v = 1; v < size; ++v) {
        for (const int& e : graph[v]) {
            rev_graph[e].emplace_back(v);
        }
    }

    std::function<void(int)> dfs_sort = [&](int cur) {
        visited[cur] = 1;
        for (const int& e : graph[cur]) {
            if (!visited[e]) {
                dfs_sort(e);
            }
        }
        stack.push_back(cur);
    };

    std::function<void(int, int)> dfs_scc = [&](int cur, int id) {
        components[cur] = id;
        for (const int& e : rev_graph[cur]) {
            if (!components[e]) {
                dfs_scc(e, id);
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

std::vector<int> sat2(std::vector<std::pair<int, int>>& statement, int n) {
    std::vector<std::vector<int>> graph(2 * n + 1);
    auto get_index = [&](int num) { return num > 0 ? num : n - num; };

    for (const auto& edge : statement) {
        graph[get_index(-edge.first)].push_back(get_index(edge.second));
        graph[get_index(-edge.second)].push_back(get_index(edge.first));
    }

    auto components = find_components(graph);
    int max_id = 0;
    for (auto cid : components) max_id = std::max(max_id, cid);
    std::vector<int> res(n + 1);

    for (int x = 1; x <= n; ++x) {
        if (components[x] == components[x + n]) {
            return {};
        }

        res[x] = components[x + n] < components[x];
    }

    return res;
}

std::pair<int, int> is_less_than(std::vector<int>& a, std::vector<int>& b) {
    int index = 0;
    while (index < a.size() && index < b.size() && a[index] == b[index]) index++;

    if (index == a.size() && index == b.size()) return {0, -1};
    if (index == a.size()) return {1, -1};
    if (index == b.size()) return {-1, -1};

    return std::make_pair<int, int>((a[index] < b[index] ? 1 : -1), (int)index);
}

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> statement;
    statement.reserve(2 * n);

    int l;
    std::cin >> l;
    std::vector<int> last_string(l);
    for (int i = 0; i < l; ++i) std::cin >> last_string[i];

    for (int i = 0; i < n - 1; ++i) {
        std::cin >> l;
        std::vector<int> string(l);
        for (int j = 0; j < l; ++j) std::cin >> string[j];

        auto [comparison, index] = is_less_than(last_string, string);
        if (comparison == 0) continue;
        if (index == -1) {
            if (comparison == 1) {
                std::swap(string, last_string);
                continue;
            }
            if (comparison == -1) {
                std::cout << "No\n";
                return 0;
            }
        }
        if (comparison == 1) {
            statement.emplace_back(last_string[index], -string[index]);
        } else {
            statement.emplace_back(last_string[index], last_string[index]);
            statement.emplace_back(-string[index], -string[index]);
        }

        std::swap(string, last_string);
    }

    auto res = sat2(statement, m);
    if (res.empty()) {
        std::cout << "No\n";
        return 0;
    }

    std::cout << "Yes\n";
    int total = 0;
    for (bool bit : res) {
        total += bit;
    }
    std::cout << total << '\n';
    for (int num = 1; num <= m; ++num) {
        if (res[num]) std::cout << num << ' ';
    }
}