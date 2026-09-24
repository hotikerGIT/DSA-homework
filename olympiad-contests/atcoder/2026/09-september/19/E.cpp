#include <iostream>
#include <vector>
#define int long long

struct Node {
    int max_value = -1;
    int max_index = -1;
    int min_value = 2e9;
    int min_index = -1;
};

class SegmentTree {
private:
    std::vector<Node> tree;
    int n;

    Node Merge(const Node& node1, const Node& node2) {
        Node res;
        res.max_value = node2.max_value;
        res.max_index = node2.max_index;
        res.min_value = node2.min_value;
        res.min_index = node2.min_index;

        if (node1.max_value > node2.max_value) {
            res.max_value = node1.max_value;
            res.max_index = node1.max_index;
        }
        if (node1.min_value < node2.min_value) {
            res.min_value = node1.min_value;
            res.min_index = node1.min_index;
        }
        return res;
    }

    void build(int index, int tree_left, int tree_right, const std::vector<Node>& start) {
        if (tree_left == tree_right) {
            tree[index] = start[tree_left];
            return;
        }
        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, start);
        build(index * 2 + 1, tree_mid + 1, tree_right, start);
        tree[index] = Merge(tree[index * 2], tree[index * 2 + 1]);
    }

    Node get(int index, int tree_left, int tree_right, int left, int right) {
        if (left <= tree_left && tree_right <= right) return tree[index];
        if (right < tree_left || tree_right < left) return Node();
        int tree_mid = (tree_left + tree_right) / 2;
        return Merge(
            get(index * 2, tree_left, tree_mid, left, right),
            get(index * 2 + 1, tree_mid + 1, tree_right, left, right)
        );
    }

    void set(int index, int tree_left, int tree_right, int pos, const Node& value) {
        if (tree_left == tree_right) {
            tree[index] = value;
            return;
        }
        int tree_mid = (tree_left + tree_right) / 2;
        if (pos <= tree_mid) set(index * 2, tree_left, tree_mid, pos, value);
        else set(index * 2 + 1, tree_mid + 1, tree_right, pos, value);
        tree[index] = Merge(tree[index * 2], tree[index * 2 + 1]);
    }

public:
    SegmentTree(const std::vector<Node>& start) : n(start.size()) {
        tree.resize(4 * n, Node());
        build(1, 0, n - 1, start);
    }

    Node get(int left, int right) {
        return get(1, 0, n - 1, left, right);
    }

    void set(int pos, const Node& value) {
        set(1, 0, n - 1, pos, value);
    }
};

signed main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) std::cin >> p[i];

    std::vector<Node> vc(n);
    for (int i = 0; i < n; ++i) {
        vc[i].max_value = vc[i].min_value = p[i];
        vc[i].max_index = vc[i].min_index = i;
    }

    SegmentTree T(vc);

    for (int i = 0; i < k; ++i) {
        int l, r;
        std::cin >> l >> r;
        --l; --r;

        Node res = T.get(l, r);

        int min_idx = res.min_index;
        int max_idx = res.max_index;

        std::swap(p[min_idx], p[max_idx]);

        Node node_min;
        node_min.max_value = node_min.min_value = p[min_idx];
        node_min.max_index = node_min.min_index = min_idx;

        T.set(min_idx, node_min);

        Node node_max;
        node_max.max_value = node_max.min_value = p[max_idx];
        node_max.max_index = node_max.min_index = max_idx;

        T.set(max_idx, node_max);
    }

    for (int i = 0; i < n; ++i) {
        std::cout << p[i] << ' ';
    }
    std::cout << std::endl;

    return 0;
}