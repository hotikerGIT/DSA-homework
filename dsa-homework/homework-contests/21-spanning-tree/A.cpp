#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>

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
};

struct Edge {
    Vertex from, to;
    int weight;

    bool operator <(const Edge& other) const {
        return weight < other.weight;
    }
};


int main() {
    int n, m, p1, p2;
    std::cin >> n >> m >> p1 >> p2;

    auto get_weight = [&](int x1, int x2, int y1, int y2) {
        return ((x1 + 1) * (x2 + 1) + p1 * (y1 + 1) * (y2 + 1)) % p2;
    };

    auto check_boundaries = [&](int x, int y) {
        return 0 <= x && x < n && 0 <= y && y < m;
    };

    std::vector<Edge> edges;

    int dirs[][2] = {
        {-1, -1},
        {0, -1},
        {-1, 0},
    };

    for (int x1 = 0; x1 < n; ++x1) {
        for (int y1 = 0; y1 < m; ++y1) {
            for (auto& [dx, dy] : dirs) {
                int x2 = x1 + dx;
                int y2 = y1 + dy;

                if (check_boundaries(x2, y2)) {
                    auto v1 = Vertex(x1, y1);
                    auto v2 = Vertex(x2, y2);
                    int weight = get_weight(x1, x2, y1, y2);

                    edges.emplace_back(v1, v2, weight);
                    edges.emplace_back(v2, v1, weight);
                }
            }
        }
    }

    std::sort(edges.begin(), edges.end());
    DSU dsu(n * m);
    int ans = 0;

    for (auto& edge : edges) {
        Vertex& v1 = edge.from, v2 = edge.to;
        int index1 = v1.x * m + v1.y;
        int index2 = v2.x * m + v2.y;

        if (dsu.share(index1, index2)) continue;
        ans += edge.weight;
        dsu.unite(index1, index2);
    }

    std::cout << ans;
}