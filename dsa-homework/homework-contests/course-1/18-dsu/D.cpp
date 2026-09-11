#include <numeric>
#include <vector>
#include <iostream>
#include <set>

class DSU {
public:
    DSU(int n) : p(n + 1), s(n + 1, 1) {
        std::iota(p.begin(), p.end(), 0);
    }

    bool share(int u, int v) { return root(u) == root(v); }

    void unite(int u, int v) {
        int ru = root(u), rv = root(v);
        if (ru == rv) {return;}
        if (s[ru] > s[rv]) {
            std::swap(u, v);
            std::swap(ru, rv);
        }
        p[ru] = rv; s[rv] += s[ru];
    }

    int root(int x) {
        if (p[x] == x) {return x;}
        int r = root(p[x]);
        return p[x] = r;
    }

private:
    std::vector<int> p, s;
};

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> edges;
    DSU d(n);

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;

        if (d.share(a, b)) edges.emplace_back(a, b);
        else d.unite(a, b);
    }

    std::set<int> roots;
    for (int i = 1; i <= n; ++i) {
        roots.insert(d.root(i));
    }

    std::cout << edges.size() << '\n';
    if (roots.size() == 1) {
        return 0;
    }

    for (auto& edge : edges) {
        auto it = roots.begin();
        int first = *it;
        roots.erase(it);
        std::cout << edge.first << ' ' << edge.second << ' ' << first << ' ' << *roots.begin() << '\n';
    }
}