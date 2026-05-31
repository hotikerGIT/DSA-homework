#include <iostream>
#include <vector>
#include <map>
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

int main() {
    int n, a, b;
    std::cin >> n >> a >> b;
    std::vector<int> numbers(n);
    std::set<int> sorted_numbers;
    for (int i = 0; i < n; ++i) {
        std::cin >> numbers[i];
        sorted_numbers.insert(numbers[i]);
    }

    std::map<int, int> cords;
    int index = 1;
    for (int num : sorted_numbers) {
        cords[num] = index++;
    }

    std::vector<int> out(n + 1, -1);
    for (int num : numbers) {
        bool flag_a = sorted_numbers.contains(a - num);
        bool flag_b = sorted_numbers.contains(b - num);

        if (!flag_a && !flag_b) {
            std::cout << "NO\n";
            return 0;
        }

        if (!flag_a) {
            out[cords[num]] = 1;
        }

        if (!flag_b) {
            out[cords[num]] = 0;
        }
    }

    std::vector<std::pair<int, int>> statement;
    statement.reserve(5 * n);
    for (int x : numbers) {
        int a_ = cords[a - x];
        int b_ = cords[b - x];
        int x_ = cords[x];

        if (out[cords[x]] == 0) {
            statement.emplace_back(-a_, -a_);
        } else if (out[cords[x]] == 1) {
            statement.emplace_back(b_, b_);
        } else {
            statement.emplace_back(-a_, x_);
            statement.emplace_back(-x_, b_);
            statement.emplace_back(-a_, b_);
        }
    }

    auto res = sat2(statement, cords.size());
    if (res.empty()) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    for (int x : numbers) {
        if (out[cords[x]] != -1) {
            std::cout << out[cords[x]] << ' ';
        } else {
            std::cout << res[cords[x]] << ' ';
        }
    }
}