#include <vector>
#include <numeric>
#include <iostream>
#include <string>
#include <map>

class dsu {
public:
    dsu(int n) : p(n), s(n, 1), relations(n, 0) {
        std::iota(p.begin(), p.end(), 0);
    }

    bool unite(int u, int v, int t) {
        auto [root_u, relation_u] = get(u);
        auto [root_v, relation_v] = get(v);

        if (root_u == root_v) { return (relation_u ^ relation_v) == t; }
        if (s[root_u] > s[root_v]) {
            std::swap(root_u, root_v);
            std::swap(relation_u, relation_v);
            t ^= 1;
        }

        p[root_u] = root_v;
        relations[root_u] = relation_u ^ relation_v ^ t;
        return true;
    }

    std::pair<int, int> get(int x) {
        if (p[x] == x) { return {x, 0}; }
        auto [parent, relation] = get(p[x]);
        relations[x] ^= relation;
        p[x] = parent;
        return {p[x], relations[x]};
    }

    int get_relation(int v, int u) {
        auto [root_u, relation_u] = get(u);
        auto [root_v, relation_v] = get(v);

        if (root_u != root_v) return 3;
        return (relation_v ^ relation_u) + 1;
    }

private:
    std::vector<int> p, s, relations;
};

int main() {
    int n, m, q;
    std::cin >> n >> m >> q;
    std::vector<std::string> strings(n);
    std::map<std::string, int> keys;
    for (int i = 0; i < n; ++i) {
        std::cin >> strings[i];
        keys[strings[i]] = i;
    }
    dsu d(n);
    for (int i = 0; i < m; ++i) {
        int t;
        std::cin >> t;
        std::string a, b;
        std::cin >> a >> b;

        if (d.unite(keys[a], keys[b], t - 1)) {
            std::cout << "YES\n";
        } else {
            std::cout << "NO\n";
        }

    }

    for (int i = 0; i < q; ++i) {
        std::string a, b;
        std::cin >> a >> b;

        std::cout << d.get_relation(keys[a], keys[b]) << '\n';
    }
}