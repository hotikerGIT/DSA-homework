#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <numeric>
#define int long long



class DSU {
public:
    DSU() = default;

    bool share(int u, int v) { return root(u) == root(v); }

    void unite(int u, int v) {
        int ru = root(u), rv = root(v);
        if (ru == rv) { return; }
        if (s[ru] > s[rv]) {
            std::swap(u, v);
            std::swap(ru, rv);
        }
        p[ru] = rv; s[rv] += s[ru];
        comps--;
    }

    int root(int x) {
        if (p[x] == x) {return x;}
        int r = root(p[x]);
        return p[x] = r;
    }

    void add_vertex(int v) {
        if (p.contains(v)) return;
        comps++;
        p[v] = v;
    }

    void add_edge(int u, int v) {
        add_vertex(v);
        add_vertex(u);
        unite(u, v);
    }

    int get_components() const { return comps; }
    int get_size() const { return p.size(); }

    void merge(DSU& from) {
        for (auto& [vertex, parent] : from.p) {
            add_edge(vertex, parent);
        }
    }

    std::map<int, int> p, s;
    int comps;
};



signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<std::pair<int, int>> controlled(n + 1);
    for (int i = 2; i <= n; ++i) {
        int a;
        std::cin >> a;
        graph[a].push_back(i);
        graph[i].push_back(a);
    }
    for (int i = 1; i <= n; ++i) {
        int a, b;
        std::cin >> a >> b;
        controlled[i] = {a, b};
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

    std::vector<DSU> vertices(n + 1);
    std::vector<int> answer(n + 1);
    for (int v : stack) {
        int big_child = -1;
        size_t max_size = 0;

        for (int to : graph[v]) {
            if (to == parents[v]) continue;
            if (vertices[to].get_size() > max_size) {
                max_size = vertices[to].get_size();
                big_child = to;
            }
        }

        if (big_child != -1) {
            vertices[v] = std::move(vertices[big_child]);
        }

        for (int to : graph[v]) {
            if (to == parents[v] || to == big_child) continue;
            vertices[v].merge(vertices[to]);
        }

        if (controlled[v].first != 0) vertices[v].add_edge(controlled[v].first, controlled[v].second);
        answer[v] = k + vertices[v].get_components() - vertices[v].get_size();
    }

    for (int i = 1; i <= n; ++i) {
        std::cout << answer[i] << '\n';
    }
}