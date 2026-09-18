#include <iostream>
#include <vector>
#define int long long

template <typename Node,
        typename UpdateNode,
        typename Merge,
        typename Update,
        typename Compose>
class SegmentTree {
private:
    std::vector<Node> tree;
    std::vector<UpdateNode> lazy;
    int n;
    Merge merge_;
    Update update_;
    Compose compose_;

private:
    void build(int index, int tree_left, int tree_right, const std::vector<Node>& start) {
        if (tree_left == tree_right) {
            tree[index] = start[tree_left];
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, start);
        build(index * 2 + 1, tree_mid + 1, tree_right, start);
        tree[index] = merge_(tree[index * 2], tree[index * 2 + 1]);
    }

    Node get(int index, int tree_left, int tree_right, int left, int right) {
        push(index, tree_left, tree_right);

        if (left <= tree_left && tree_right <= right) return tree[index];
        if (right < tree_left || tree_right < left) return Node();

        int tree_mid = (tree_left + tree_right) / 2;
        return merge_(
                get(index * 2, tree_left, tree_mid, left, right),
                get(index * 2 + 1, tree_mid + 1, tree_right, left, right)
        );
    }

    void update(int index, int tree_left, int tree_right, int left, int right, UpdateNode& update_node) {
        if (left <= tree_left && tree_right <= right) {
            compose_(lazy[index], update_node);
            push(index, tree_left, tree_right);
            return;
        }

        push(index, tree_left, tree_right);

        if (right < tree_left || tree_right < left) return;

        int tree_mid = (tree_left + tree_right) / 2;
        update(index * 2, tree_left, tree_mid, left, right, update_node);
        update(index * 2 + 1, tree_mid + 1, tree_right, left, right, update_node);

        tree[index] = merge_(tree[index * 2], tree[index * 2 + 1]);
    }

    void push(int index, int tree_left, int tree_right) {
        update_(tree[index], lazy[index]);

        if (tree_left != tree_right) {
            compose_(lazy[index * 2], lazy[index]);
            compose_(lazy[index * 2 + 1], lazy[index]);
        }

        lazy[index] = UpdateNode();
    }

public:
    SegmentTree(const std::vector<Node>& start,
                Merge merge,
                Update update,
                Compose compose)
            : n(start.size())
            , merge_(merge)
            , update_(update)
            , compose_(compose) {
        tree.resize(4 * n, Node());
        lazy.resize(4 * n, UpdateNode());
        build(1, 0, n - 1, start);
    }

    void update(int left, int right, UpdateNode& update_node) {
        update(1, 0, n - 1, left, right, update_node);
    }

    Node get(int left, int right) {
        return get(1, 0, n - 1, left, right);
    }
};

struct Node {
    std::string str;
    int k0 = 0, k1 = 0;
};

struct UpdateNode {

    bool operator==(const UpdateNode& other) const {
        bool is_equal = true;
        return is_equal;
    }
};

Node Merge(const Node& node1, const Node& node2) {
    Node res;

    res.str = node1.str + node2.str;
    res.k0 = node1.k0 + (node1.str.size() % 2 == 0 ? node2.k0 : node2.k1);
    res.k1 = node1.k1 + (node1.str.size() % 2 == 0 ? node2.k1 : node2.k0);

    return res;
}

void Compose(UpdateNode& node1, const UpdateNode& node2) {
}

void Update(Node& node, const UpdateNode& update_node) {
    if (update_node == UpdateNode()) return;
}

void solve() {
    int n, q;
    std::string s;
    std::cin >> n >> q >> s;
    std::vector<Node> vc(n);

    for (int i = 0; i < n; ++i) {
        vc[i].str = s[i];
        vc[i].k0 = s[i] == '0' ? 0 : 1;
        vc[i].k1 = s[i] == '1' ? 0 : 1;
    }

    auto merge_func = Merge;
    auto update_func = Update;
    auto compose_func = Compose;

    SegmentTree<Node,
            UpdateNode,
            decltype(merge_func),
            decltype(update_func),
            decltype(compose_func)> T(vc, merge_func, update_func, compose_func);

    for (int i = 0; i < q; ++i) {
        int l, r, k;
        std::cin >> l >> r >> k;

        auto res = T.get(l - 1, r - 1);
        int min = std::min(res.k0, res.k1);

        std::cout << (min <= k ? "YES\n" : "NO\n");
    }
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}