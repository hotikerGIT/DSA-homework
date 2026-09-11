#include <iostream>
#include <vector>
#include <map>
#include <functional>
#define int long long

struct Vertex {
    std::map<int, int> color_count;
    int max_freq = 0;
    int sum = 0;

    Vertex() = default;
};

void add_color(Vertex& v, int color, int count) {
    int old_freq = v.color_count[color];
    int new_freq = old_freq + count;
    v.color_count[color] = new_freq;

    if (new_freq > v.max_freq) {
        v.max_freq = new_freq;
        v.sum = color;
    } else if (new_freq == v.max_freq) {
        v.sum += color;
    }
}

void merge(Vertex& to, Vertex& from) {
    for (auto& [color, freq] : from.color_count) {
        add_color(to, color, freq);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> colors(n + 1);
    for (int i = 1; i <= n; ++i) std::cin >> colors[i];
    std::vector<std::vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }

    std::vector<int> stack, visited(n + 1);
    std::vector<int> parents(n + 1);
    std::function<void(int, int)> top_sort = [&](int cur, int prev) {
        parents[cur] = prev;
        visited[cur] = 1;

        for (auto& next : graph[cur]) {
            if (!visited[next]) top_sort(next, cur);
        }

        stack.push_back(cur);
    };

    top_sort(1, -1);

    std::vector<Vertex> vertices(n + 1);
    std::vector<int> answer(n + 1);
    for (int v : stack) {
        int big_child = -1;
        size_t max_size = 0;

        for (int to : graph[v]) {
            if (to == parents[v]) continue;
            if (vertices[to].color_count.size() > max_size) {
                max_size = vertices[to].color_count.size();
                big_child = to;
            }
        }

        if (big_child != -1) {
            vertices[v] = std::move(vertices[big_child]);
        }

        for (int to : graph[v]) {
            if (to == parents[v] || to == big_child) continue;
            merge(vertices[v], vertices[to]);
        }

        add_color(vertices[v], colors[v], 1);
        answer[v] = vertices[v].sum;
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << answer[i] << ' ';
    }
}