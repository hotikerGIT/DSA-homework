#include <iostream>
#include <vector>
#include <tuple>
#include <string>

#define int long long

class FenwickTree {
private:
    int n, m;
    std::vector<std::vector<int>> tree;

    int query_prefix(int x, int y) {
        int res = 0;
        for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
            for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
                res += tree[i][j];
            }
        }
        return res;
    }

    void update(int x, int y, int delta) {
        for (int i = x; i < n; i = i | (i + 1)) {
            for (int j = y; j < m; j = j | (j + 1)) {
                tree[i][j] += delta;
            }
        }
    }

public:
    int query_rect(int x1, int y1, int x2, int y2) {
        x1--; y1--; x2--; y2--;
        return query_prefix(x2, y2)
               - query_prefix(x1 - 1, y2)
               - query_prefix(x2, y1 - 1)
               + query_prefix(x1 - 1, y1 - 1);
    }

    void add(int x, int y, int k) {
        x--; y--;
        update(x, y, k);
    }

    FenwickTree(int n, int m) : n(n), m(m) {
        tree.assign(n, std::vector<int>(m, 0));
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, k;
    std::cin >> n >> m >> k;

    std::vector<std::vector<std::tuple<int, int, int>>> garlands(k);

    for (int g = 0; g < k; ++g) {
        int len;
        std::cin >> len;
        garlands[g].reserve(len);
        for (int j = 0; j < len; ++j) {
            int x, y, w;
            std::cin >> x >> y >> w;
            garlands[g].emplace_back(x, y, w);
        }
    }

    FenwickTree FT(n, m);
    std::vector<bool> state(k, true);
    std::vector<bool> change(k, false);

    for (int g = 0; g < k; ++g) {
        for (auto [x, y, w] : garlands[g]) {
            FT.add(x, y, w);
        }
    }

    int q;
    std::cin >> q;

    while (q--) {
        std::string cmd;
        std::cin >> cmd;

        if (cmd == "SWITCH") {
            int idx;
            std::cin >> idx;
            --idx;
            change[idx] = !change[idx];

        } else {
            for (int i = 0; i < k; ++i) {
                if (!change[i]) continue;

                if (state[i]) {
                    for (auto [x, y, w] : garlands[i]) {
                        FT.add(x, y, -w);
                    }
                } else {
                    for (auto [x, y, w] : garlands[i]) {
                        FT.add(x, y, w);
                    }
                }

                state[i] = !state[i];
            }

            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            std::cout << FT.query_rect(x1, y1, x2, y2) << '\n';
            change.assign(k, false);
        }
    }

    return 0;
}