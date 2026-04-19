#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

struct Node {
    int prefix, suffix, best;
    Node() = default;
};

class SegmentTree {
    int n;
    std::vector<Node> tree;
    std::vector<int> difference;

    static int sign(int num) {
        if (num < 0) return -1;
        if (num > 0) return 1;
        return 0;
    }

    static bool check(int a, int b) {
        return a != 0 && b != 0 && sign(a) >= sign(b);
    }

    void merge(int index, int tree_left, int tree_right) {
        int tree_mid = (tree_left + tree_right) / 2;

        tree[index].best = std::max(tree[index*2].best, tree[index*2+1].best);
        tree[index].prefix = tree[index*2].prefix;
        tree[index].suffix = tree[index*2+1].suffix;

        if (tree_mid >= 0 && tree_mid < n && tree_mid+1 < n &&
            check(difference[tree_mid], difference[tree_mid+1])) {
            tree[index].best = std::max(tree[index].best,
                                        tree[index*2].suffix + tree[index*2+1].prefix);

            if (tree[index*2].prefix == tree_mid - tree_left + 1)
                tree[index].prefix += tree[index*2+1].prefix;

            if (tree[index*2+1].suffix == tree_right - tree_mid)
                tree[index].suffix += tree[index*2].suffix;
        }
    }

    void build(int index, int tree_left, int tree_right) {
        if (tree_left == tree_right) {
            tree[index].prefix = 1;
            tree[index].best = 1;
            tree[index].suffix = 1;
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index*2, tree_left, tree_mid);
        build(index*2+1, tree_mid+1, tree_right);
        merge(index, tree_left, tree_right);
    }

    void update(int index, int tree_left, int tree_right, int pos) {
        if (tree_left == tree_right) {
            tree[index].prefix = 1;
            tree[index].best = 1;
            tree[index].suffix = 1;
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        if (pos <= tree_mid) update(index*2, tree_left, tree_mid, pos);
        else update(index*2+1, tree_mid+1, tree_right, pos);
        merge(index, tree_left, tree_right);
    }

public:
    explicit SegmentTree(const std::vector<int>& vec) {
        n = vec.size() - 1;
        if (n <= 0) return;
        tree.resize(4 * n, Node());
        difference.resize(n);
        for (int i = 0; i < n; ++i) difference[i] = vec[i+1] - vec[i];
        build(1, 0, n-1);
    }

    void query(int left, int right, int x) {
        if (n <= 0) {
            std::cout << "1\n";
            return;
        }

        if (left > 0) {
            difference[left-1] += x;
            update(1, 0, n-1, left-1);
        }

        if (right < n) {
            difference[right] -= x;
            update(1, 0, n-1, right);
        }

        std::cout << std::max({tree[1].prefix, tree[1].best, tree[1].suffix}) + 1 << '\n';
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    SegmentTree T(a);

    int q;
    std::cin >> q;
    while (q--) {
        int l, r, x;
        std::cin >> l >> r >> x;
        T.query(l-1, r-1, x);
    }

    return 0;
}