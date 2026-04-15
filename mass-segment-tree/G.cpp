#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

struct Node {
    int max_y;
    std::set<int> y_coords;
};

class SegmentTree {
private:
    std::vector<int> coords_x;
    int n;
    std::vector<std::set<std::pair<int, int>>> tree;

    void add(int index, int tree_left, int tree_right, int x, int y) {
        tree[index].insert({x, y});
        if (tree_left == tree_right) return;
        int tree_mid = (tree_left + tree_right) / 2;
        if (x <= coords_x[tree_mid])
            add(index * 2, tree_left, tree_mid, x, y);
        else
            add(index * 2 + 1, tree_mid + 1, tree_right, x, y);
    }

    void remove(int index, int tree_left, int tree_right, int x, int y) {
        tree[index].erase({x, y});
        if (tree_left == tree_right) return;
        int tree_mid = (tree_left + tree_right) / 2;
        if (x <= coords_x[tree_mid])
            remove(index * 2, tree_left, tree_mid, x, y);
        else
            remove(index * 2 + 1, tree_mid + 1, tree_right, x, y);
    }

    void get(int index, int tree_left, int tree_right, int x0, int y0, std::pair<int, int>& res) {
        if (coords_x[tree_right] < x0 + 1) return;
        if (coords_x[tree_left] >= x0 + 1) {
            auto it = tree[index].lower_bound({x0 + 1, -1});
            if (it != tree[index].end()) {
                if (res.first == -1 ||
                    it->first < res.first ||
                    (it->first == res.first && it->second < res.second)) {
                    res = *it;
                }
            }
            return;
        }
        int tree_mid = (tree_left + tree_right) / 2;
        get(index * 2, tree_left, tree_mid, x0, y0, res);
        get(index * 2 + 1, tree_mid + 1, tree_right, x0, y0, res);
    }

public:
    SegmentTree(const std::set<int>& cy)
        : coords_x(cy.begin(), cy.end())
        , n(coords_x.size())
        , tree(4 * n) {}

    void insert(int x, int y) {
        add(1, 0, n - 1, x, y);
    }

    void erase(int x, int y) {
        remove(1, 0, n - 1, x, y);
    }

    void out(int x, int y) {
        std::pair<int, int> res = {-1, -1};
        get(1, 0, n - 1, x, y, res);
        if (res.first == -1) {
            std::cout << -1 << '\n';
            return;
        }
        std::cout << res.first << ' ' << res.second << '\n';
    }
};

struct Query {
    std::string type;
    int x, y;
    Query(std::string s, int x, int y) : type(std::move(s)), x(x), y(y) {}
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int q;
    std::cin >> q;
    std::vector<Query> queries;
    queries.reserve(q);
    std::set<int> coords_y;

    for (int i = 0; i < q; ++i) {
        std::string type;
        int x, y;
        std::cin >> type >> x >> y;
        queries.emplace_back(type, x, y);
        if (type != "find") {
            coords_y.insert(y);
        }
    }

    SegmentTree T(coords_y);

    for (const auto& Q : queries) {
        if (Q.type == "add") T.insert(Q.x, Q.y);
        else if (Q.type == "remove") T.erase(Q.x, Q.y);
        else T.out(Q.x, Q.y);
    }

    return 0;
}



#include  <iostream>
#include  <vector>

using namespace std;

#define int long long

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> data(n);
    for (autol& el: data) {cin >> el;}

    for (int i = 0; i < q; i++) {
        int tp, a, b;
        cin >> tp >> a >> b;
        if (tp == 0) {

        }
    }
}

signed main() {
    cin.tie();
    cout.tie();
    ios_base::sync_with_stdio(false);

    int cr = 1;
    //cin >> cr;
    for (int i = 0 ; i < cr; i++) {
        solve();
    }
    return 0;
}