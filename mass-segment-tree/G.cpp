#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>

struct Node {
    int max_y = 0;
    std::set<int> ys;

    Node() = default;
};

struct TreeIndex {
    int index, tree_left, tree_right;
};

class SegmentTree {
private:
    std::vector<int> coords_x;
    int n;
    std::vector<Node> tree;
    std::vector<TreeIndex> query_indexes;

    void add(int index, int tree_left, int tree_right, int x, int y) {
        if (tree_left == tree_right) {
            tree[index].ys.insert(y);
            tree[index].max_y = std::max(tree[index].max_y, y);
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        if (x <= coords_x[tree_mid])
            add(index * 2, tree_left, tree_mid, x, y);
        else
            add(index * 2 + 1, tree_mid + 1, tree_right, x, y);

        tree[index].max_y = std::max(tree[index * 2].max_y, tree[index * 2 + 1].max_y);
    }

    void remove(int index, int tree_left, int tree_right, int x, int y) {
        if (tree_left == tree_right) {
            tree[index].ys.erase(y);
            tree[index].max_y = tree[index].ys.empty() ? 0 : *tree[index].ys.rbegin();
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        if (x <= coords_x[tree_mid])
            remove(index * 2, tree_left, tree_mid, x, y);
        else
            remove(index * 2 + 1, tree_mid + 1, tree_right, x, y);

        tree[index].max_y = std::max(tree[index * 2].max_y, tree[index * 2 + 1].max_y);
    }

    void get(int index, int tree_left, int tree_right, int x0, int y0) {
        if (coords_x[tree_right] < x0 + 1) return;
        if (coords_x[tree_left] >= x0 + 1) {
            if (tree[index].max_y > y0) query_indexes.emplace_back(index, tree_left, tree_right);
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        get(index * 2, tree_left, tree_mid, x0, y0);
        get(index * 2 + 1, tree_mid + 1, tree_right, x0, y0);
    }

    std::pair<int, int> descend(int index, int tree_left, int tree_right, int y0) {
        if (tree_left == tree_right) {
            auto it = tree[index].ys.upper_bound(y0);
            if (it != tree[index].ys.end()) {
                return {coords_x[tree_left], *it};
            }
            return {-1, -1};
        }

        if (tree[index].max_y <= y0) return {-1, -1};

        int tree_mid = (tree_left + tree_right) / 2;
        auto left = descend(index * 2, tree_left, tree_mid, y0);
        if (left.first != -1) return left;
        return descend(index * 2 + 1, tree_mid + 1, tree_right, y0);
    }

public:
    SegmentTree(const std::set<int>& cx)
            : coords_x(cx.begin(), cx.end())
            , n(coords_x.size())
            , tree(4 * n) {}

    void insert(int x, int y) {
        add(1, 0, n - 1, x, y);
    }

    void erase(int x, int y) {
        remove(1, 0, n - 1, x, y);
    }

    void out(int x, int y) {
        query_indexes.clear();
        query_indexes.reserve(20);
        get(1, 0, n - 1, x, y);

        for (auto & query_index : query_indexes) {
            auto res = descend(query_index.index, query_index.tree_left, query_index.tree_right, y);
            if (res.first != -1) {
                std::cout << res.first << ' ' << res.second << '\n';
                return;
            }
        }

        std::cout << "-1\n";
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
    std::set<int> coords_x;

    for (int i = 0; i < q; ++i) {
        std::string type;
        int x, y;
        std::cin >> type >> x >> y;
        queries.emplace_back(type, x, y);
        coords_x.insert(x);
    }

    SegmentTree T(coords_x);

    for (const auto& Q : queries) {
        if (Q.type == "add") T.insert(Q.x, Q.y);
        else if (Q.type == "remove") T.erase(Q.x, Q.y);
        else T.out(Q.x, Q.y);
    }

    return 0;
}