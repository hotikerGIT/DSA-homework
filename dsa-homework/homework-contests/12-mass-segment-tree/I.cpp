#include <iostream>
#include <vector>

const int NEUTRAL_MIN = 2e9;
const int NEUTRAL_MAX = -2e9;

struct Node {
    int max_left;
    int min_right;

    Node(int l, int r) : max_left(l), min_right(r) {}
    Node() : max_left(NEUTRAL_MAX), min_right(NEUTRAL_MIN) {}

    int length() {
        if (max_left <= min_right) return min_right - max_left + 1;
        return 0;
    }

    static Node merge(const Node& c1, const Node& c2) {
        auto res = Node();
        res.max_left = std::max(c1.max_left, c2.max_left);
        res.min_right = std::min(c2.min_right, c1.min_right);
        return res;
    }
};

class SegmentTree {
private:
    std::vector<Node> tree;
    int n;

    void build(int index, int tree_left, int tree_right, const std::vector<std::pair<int, int>>& vec) {
        if (tree_left == tree_right) {
            tree[index] = Node(vec[tree_right].first, vec[tree_right].second);
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, vec);
        build(index * 2 + 1, tree_mid + 1, tree_right, vec);

        tree[index] = Node::merge(tree[index * 2], tree[index * 2 + 1]);
    }

    Node get(int index, int tree_left, int tree_right, int left, int right) {
        if (left <= tree_left && tree_right <= right) return tree[index];
        if (tree_right < left || right < tree_left) return {NEUTRAL_MAX, NEUTRAL_MIN};

        int tree_mid = (tree_left + tree_right) / 2;
        return Node::merge(get(index * 2, tree_left, tree_mid, left, right),
                           get(index * 2 + 1, tree_mid + 1, tree_right, left, right));
    }

    void update(int index, int tree_left, int tree_right, int pos, int l, int r) {
        if (tree_left == tree_right) {
            tree[index] = Node(l, r);
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        if (pos <= tree_mid) update(index * 2, tree_left, tree_mid, pos, l, r);
        else update(index * 2 + 1, tree_mid + 1, tree_right, pos, l, r);

        tree[index] = Node::merge(tree[index * 2], tree[index * 2 + 1]);
    }

public:
    SegmentTree(const std::vector<std::pair<int, int>>& vec) {
        n = vec.size();
        tree.resize(4 * n, Node());
        build(1, 0, n - 1, vec);
    }

    void set(int pos, int left, int right) {
        update(1, 0, n - 1, pos, left, right);
    }

    void out(int left, int right) {
        std::cout << get(1, 0 , n - 1, left, right).length() << '\n';
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        int l, r;
        std::cin >> l >> r;
        a[i] = {l, r};
    }

    SegmentTree T = SegmentTree(a);

    for (int i = 0; i < q; ++i) {
        char type;
        std::cin >> type;

        if (type == 'C') {
            int p, l, r;
            std::cin >> p >> l >> r;
            T.set(p - 1, l, r);
        }

        else {
            int l, r;
            std::cin >> l >> r;
            T.out(l - 1, r - 1);
        }
    }

    return 0;
}