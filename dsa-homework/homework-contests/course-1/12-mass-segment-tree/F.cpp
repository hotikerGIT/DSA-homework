#include <iostream>
#include <vector>
#define int long long

struct Node {
    int sum = 0, count = 0;
};

class InnerTree {
private:
    int n;
    std::vector<Node> tree;
    void add(int index, int tree_left, int tree_right, int pos, int delta_sum, int delta_count) {
        if (tree_left == tree_right) {
            tree[index].sum += delta_sum;
            tree[index].count += delta_count;
            return;
        }

        int mid = (tree_left + tree_right) / 2;
        if (pos <= mid) add(index * 2, tree_left, mid, pos, delta_sum, delta_count);
        else add(index * 2 + 1, mid + 1, tree_right, pos, delta_sum, delta_count);

        tree[index].sum = tree[index * 2].sum + tree[index * 2 + 1].sum;
        tree[index].count = tree[index * 2].count + tree[index * 2 + 1].count;
    }

public:
    InnerTree() {
        n = 1e5 + 1;
        tree.resize(4 * n);
    }

    void add(int pos, int delta_sum, int delta_count) {
        add(1, 0, n - 1, pos, delta_sum, delta_count);
    }

    Node& get_node(int index) {
        return tree[index];
    }
};

class SegmentTree {
private:
    int n;
    std::vector<InnerTree*> tree;
    std::vector<int> outer_indices;

    void build(int index, int tree_left, int tree_right, const std::vector<int>& vec) {
        tree[index] = new InnerTree();

        for (int i = tree_left; i <= tree_right; ++i) {
            tree[index]->add(vec[i], vec[i], 1);
        }

        if (tree_left == tree_right) return;

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, vec);
        build(index * 2 + 1, tree_mid + 1, tree_right, vec);
    }

    void update(int index, int tree_left, int tree_right, int pos, int old_value, int new_value) {
        tree[index]->add(old_value, -old_value, -1);
        tree[index]->add(new_value, new_value, 1);

        if (tree_left == tree_right) return;

        int tree_mid = (tree_left + tree_right) / 2;
        if (pos <= tree_mid) update(index * 2, tree_left, tree_mid, pos, old_value, new_value);
        else update(index * 2 + 1, tree_mid + 1, tree_right, pos, old_value, new_value);
    }

    void get_trees(int index, int tree_left, int tree_right, int left, int right) {
        if (left <= tree_left && tree_right <= right) {
            outer_indices.push_back(index);
            return;
        }

        if (tree_right < left || right < tree_left) return;

        int tree_mid = (tree_left + tree_right) / 2;
        get_trees(index * 2, tree_left, tree_mid, left, right);
        get_trees(index * 2 + 1, tree_mid + 1, tree_right, left, right);
    }

    int get(int inner_index, int val_left, int val_right, int k) {
        if (k == 0 || outer_indices.empty()) return 0;

        if (val_left == val_right) {
            return val_left * k;
        }

        int left_count = 0;
        int left_sum = 0;
        int mid = (val_left + val_right) / 2;

        for (auto outer_idx : outer_indices) {
            Node& node = tree[outer_idx]->get_node(inner_index * 2);
            left_count += node.count;
            left_sum += node.sum;
        }

        if (k <= left_count) {
            std::vector<int> new_outer = outer_indices;
            std::swap(outer_indices, new_outer);
            return get(inner_index * 2, val_left, mid, k);
        } else {
            std::vector<int> new_outer = outer_indices;
            std::swap(outer_indices, new_outer);
            return left_sum + get(inner_index * 2 + 1, mid + 1, val_right, k - left_count);
        }
    }

public:
    SegmentTree(const std::vector<int>& vec) : n(vec.size()) {
        tree.resize(4 * n, nullptr);
        build(1, 0, n - 1, vec);
    }

    ~SegmentTree() {
        for (auto t : tree) {
            delete t;
        }
    }

    void set(int pos, int old_value, int new_value) {
        update(1, 0, n - 1, pos, old_value, new_value);
    }

    int out(int left, int right, int k) {
        if (k == 0) return 0;
        outer_indices.clear();
        get_trees(1, 0, n - 1, left, right);
        return get(1, 0, 1e5, k);
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    SegmentTree T(a);
    int q;
    std::cin >> q;

    int last = 0;
    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            l ^= last;
            r ^= last;
            k ^= last;

            last = T.out(l - 1, r - 1, k);
            std::cout << last << '\n';
        } else {
            int id, new_pts;
            std::cin >> id >> new_pts;

            id ^= last;
            new_pts ^= last;

            T.set(id - 1, a[id - 1], new_pts);
            a[id - 1] = new_pts;
        }
    }

    return 0;
}