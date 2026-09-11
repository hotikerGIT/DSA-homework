#include <numeric>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>

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
};


int main() {
    freopen("maxincycle.in", "r", stdin);
    freopen("maxincycle.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;
    std::vector<Edge> edges;
    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        edges.emplace_back(a, b);
        // edges.emplace_back(b, a, i);
    }
    DSU dsu(n + 1);
    std::set<int> res;

    for (int i = 0; i < m; ++i) {
        auto& [from, to] = edges[i];

        if (dsu.share(from, to)) {
            res.insert(i);

        } else {
            dsu.unite(from, to);
        }
    }

    std::cout << m - res.size() << '\n';
    for (int i = 0; i < m; ++i) {
        if (!res.contains(i)) std::cout << i + 1 << ' ';
    }
}