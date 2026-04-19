#include <numeric>
#include <vector>
#include <iostream>
#include <functional>

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
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    DSU d(n);
    std::vector<int> next(n + 2);
    for (int i = 0; i <= n + 1; ++i) {
        next[i] = i;
    }

    std::function<int(int)> get_next = [&](int v) -> int {
        if (v > n) return n + 1;
        if (next[v] == v) return v;
        return next[v] = get_next(next[v]);
    };

    for (int i = 0; i < q; ++i) {
        int t, x, y;
        std::cin >> t >> x >> y;

        if (t == 1) {
            d.unite(x, y);

        } else if (t == 2) {
            for (int v = get_next(x + 1); v <= y; v = get_next(v + 1)) {
                d.unite(x, v);
                next[v] = get_next(v + 1);
            }
            
        } else {
            std::cout << (d.share(x, y) ? "YES\n" : "NO\n");
        }
    }
}