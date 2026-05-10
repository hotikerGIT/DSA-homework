#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <map>
#include <functional>
#define int long long

class DSU {
public:
    DSU(int n) : p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
    }

    bool share(int u, int v) {return root(u) == root(v);}

    void unite(int u, int v) {
        int ru = root(u), rv = root(v);
        if (ru == rv) {return;}
        if (s[ru] > s[rv]) {
            std::swap(u, v);
            std::swap(ru, rv);
        }
        p[ru] = rv; s[rv] += s[ru];
    }

private:
    std::vector<int> p, s;

    int root(int x) {
        if (p[x] == x) {return x;}
        int r = root(p[x]);
        return p[x] = r;
    }
};

struct Edge {
    int from, to;
    int gold, silver;

    Edge() : from(-1), to(-1), gold(-1), silver(-1) {}
    Edge(int a, int b, int c, int d) : from(a), to(b), gold(c), silver(d) {}

    bool operator<(const Edge& other) const {
        return silver < other.silver;
    }

    Edge reverse() const {
        return {to, from, gold, silver};
    }

    bool operator==(const Edge& other) const {
        return (
                from == other.from &&
                to == other.to &&
                gold == other.gold &&
                silver == other.silver
                );
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, g, s;
    std::cin >> n >> m >> g >> s;

    std::map<int, std::vector<Edge>> order;
    for (int i = 0; i < m; ++i) {
        int a, b, wg, ws;
        std::cin >> a >> b >> wg >> ws;
        order[wg].emplace_back(a, b, wg, ws);
    }

    std::vector<std::vector<Edge>> spanning_graph(n + 1);
    DSU dsu(n + 1);
    int answer = 3e18;

    std::vector<int> visited;
    std::function<Edge(int, Edge, int, Edge)> dfs = [&](int cur, Edge prev, int target, Edge choice) {
        visited[cur] = true;

        for (auto& next : spanning_graph[cur]) {
            if (next == prev.reverse()) continue;
            if (next.to == target) {
                return std::max(next, choice);
            }

            if (visited[next.to]) continue;

            Edge result = dfs(next.to, next, target, std::max(next, choice));

            if (result.from != -1) return result;
        }

        return Edge();
    };

    std::function<void(Edge&)> del_max_cycle = [&](Edge& start) {
        visited.clear();
        visited.resize(n + 1);
        Edge target = dfs(start.from, Edge(), start.from, start);
        int a =  target.from, b = target.to, c = target.silver;

        for (int i = 0; i < spanning_graph[a].size(); ++i) {
            auto& edge = spanning_graph[a][i];

            if (edge.to == b && edge.silver == c) {
                spanning_graph[a].erase(spanning_graph[a].begin() + i);
            }
        }

        for (int i = 0; i < spanning_graph[b].size(); ++i) {
            auto& edge = spanning_graph[b][i];

            if (edge.to == a && edge.silver == c) {
                spanning_graph[b].erase(spanning_graph[b].begin() + i);
            }
        }
    };

    std::function<int()> find_max = [&]() {
        int res = 0;
        int count_edges = 0;
        for (auto& edges : spanning_graph) {
            for (auto& edge : edges) {
                count_edges++;
                res = std::max(res, edge.silver);
            }
        }
        return (count_edges / 2 == n - 1) ? res : -1;
    };

    for (auto& [gold_cost, edges] : order) {
        for (auto& edge : edges) {
            spanning_graph[edge.from].push_back(edge);
            spanning_graph[edge.to].emplace_back(edge.reverse());

            if (dsu.share(edge.from, edge.to)) {
                del_max_cycle(edge);

            } else {
                dsu.unite(edge.from, edge.to);
            }
        }

        int max_silver = find_max();
        if (max_silver == -1) continue;
        answer = std::min(answer, gold_cost * g + max_silver * s);
    }

    std::cout << (answer < 3e18 ? answer : -1);
}