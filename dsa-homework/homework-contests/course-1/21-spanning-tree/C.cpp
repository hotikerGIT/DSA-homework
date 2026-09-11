#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>

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

struct Vertex {
    int x, y;

    bool operator==(const Vertex& other) const {
        return x == other.x && y == other.y;
    }
};

struct Edge {
    int from, to;
    double weight;

    bool operator <(const Edge& other) const {
        return weight < other.weight;
    }
};

int main() {
    int n;
    std::cin >> n;
    std::vector<Vertex> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    auto get_weight = [](Vertex& v1, Vertex& v2) {
        return sqrt(
            (v1.x - v2.x) * (v1.x - v2.x) +
            (v1.y - v2.y) * (v1.y - v2.y)
            );
    };

    std::vector<Edge> edges;
    for (int i = 0; i < points.size(); ++i) {
        for (int j = 0; j < points.size(); ++j) {
            if (i == j) continue;
            edges.emplace_back(i, j, get_weight(points[i], points[j]));
        }
    }
    std::sort(edges.begin(), edges.end());
    double ans = 0;
    std::vector<std::pair<int, int>> out;
    DSU dsu(n);

    for (auto& [v1, v2, weight] : edges) {
        if (dsu.share(v1, v2)) continue;
        ans += weight;
        dsu.unite(v1, v2);
        out.emplace_back(v1, v2);
    }

    std::cout << std::fixed << std::setprecision(6) << ans << '\n' << n - 1 << '\n';
    for (auto& [i, j] : out) {
        std::cout << i + 1 << ' ' << j + 1 << '\n';
    }
}