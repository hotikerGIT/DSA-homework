#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#define int long long

struct Node {
    int left, right;
    int mex = 1;
    int minc = 1e18;
    int lazy = 0;

    void apply_lazy(int op) {
        if (op == 0) return;

        if (op == 1) {
            mex = right + 1;
            minc = left;
            lazy = 1;
        } else if (op == 2) {
            mex = left;
            minc = right + 1;
            lazy = 2;
        } else if (op == 3) {
            std::swap(mex, minc);
            if (lazy == 0) lazy = 3;
            else if (lazy == 1) lazy = 2;
            else if (lazy == 2) lazy = 1;
            else lazy = 0;
        }
    }
};

class SegmentTree {
private:
    std::vector<Node> tree;
    int n;
    std::vector<int> coords;

    void push(int index, int tree_left, int tree_right) {
        if (tree[index].lazy == 0 || tree_left == tree_right) return;

        tree[index * 2].apply_lazy(tree[index].lazy);
        tree[index * 2 + 1].apply_lazy(tree[index].lazy);

        tree[index].lazy = 0;
    }

    void recalc(int index) {
        if (tree[index * 2].mex > tree[index * 2].right) {
            tree[index].mex = tree[index * 2 + 1].mex;
        } else {
            tree[index].mex = tree[index * 2].mex;
        }

        if (tree[index * 2].minc <= tree[index * 2].right) {
            tree[index].minc = tree[index * 2].minc;
        } else {
            tree[index].minc = tree[index * 2 + 1].minc;
        }
    }

    void build(int index, int tree_left, int tree_right) {
        if (tree_left == tree_right) {
            tree[index].left = coords[tree_left];
            tree[index].right = coords[tree_right];
            tree[index].mex = coords[tree_left];
            tree[index].minc = coords[tree_right] + 1;
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid);
        build(index * 2 + 1, tree_mid + 1, tree_right);
        recalc(index);
        tree[index].left = tree[index * 2].left;
        tree[index].right = tree[index * 2 + 1].right;
    }

    void update(int index, int tree_left, int tree_right, int left, int right, int op) {
        if (left <= tree[index].left && tree[index].right <= right) {
            tree[index].apply_lazy(op);
            return;
        }
        if (tree[index].right < left || right < tree[index].left) return;
        push(index, tree_left, tree_right);

        int tree_mid = (tree_left + tree_right) / 2;
        update(index * 2, tree_left, tree_mid, left, right, op);
        update(index * 2 + 1, tree_mid + 1, tree_right, left, right, op);

        recalc(index);
    }

public:
    SegmentTree(const std::vector<int>& c) : coords(c) {
        n = c.size();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    int get() {
        return tree[1].mex;
    }

    void q_add(int left, int right) {
        update(1, 0, n - 1, left, right, 1);
    }

    void q_remove(int left, int right) {
        update(1, 0, n - 1, left, right, 2);
    }

    void q_swap(int left, int right) {
        update(1, 0, n - 1 , left, right, 3);
    }
};

struct Query {
    int type, left, right;
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;
    std::vector<Query> queries;
    queries.reserve(q);
    std::set<int> coords;
    coords.insert(1);

    for (int i = 0; i < q; ++i) {
        int type, left, right;
        std::cin >> type >> left >> right;
        queries.emplace_back(type, left, right);
        coords.insert(left);
        coords.insert(right);
        coords.insert(right + 1);
    }

    std::vector<int> tree_coords(coords.begin(), coords.end());
    std::unordered_map<int, int> keys;
    for (int i = 0; i < tree_coords.size(); ++i) {
        int num = tree_coords[i];
        keys[num] = i;
    }

    SegmentTree T = SegmentTree(tree_coords);
    for (auto& Q : queries) {
        if (Q.type == 1) T.q_add(Q.left, Q.right);
        else if (Q.type == 2) T.q_remove(Q.left, Q.right);
        else T.q_swap(Q.left, Q.right);

        std::cout << T.get() << '\n';
    }
}