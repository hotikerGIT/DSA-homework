#include <vector>
#include <iostream>
#define int long long

class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;
    int pow = 0;

    void build(std::vector<int>& vec, int index, int left, int right, int oper) {
        if (left == right) {
            tree[index] = vec[left];
        }

        else {
            int middle = (left + right) / 2;
            build(vec, index * 2, left, middle, oper ^ 1);
            build(vec, index * 2 + 1, middle + 1, right, oper ^ 1);

            if (oper == 0) tree[index] = tree[index * 2] | tree[index * 2 + 1];
            else tree[index] = tree[index * 2] ^ tree[index * 2 + 1];
        }
    }

    int query(int index, int tree_left, int tree_right, int left, int right, int oper) {
        if (left > right) return 0;
        if (tree_left >= left && tree_right <= right) return tree[index];
        int tree_middle = (tree_left + tree_right) / 2;
        int q_left = query(index * 2, tree_left, tree_middle, left, std::min(right, tree_middle), oper ^ 1);
        int q_right = query(index * 2 + 1, tree_middle + 1, tree_right, std::max(left, tree_middle + 1), right, oper ^ 1);

        if (oper == 0) return q_left | q_right;
        return q_left ^ q_right;
    }

    void update(int index, int tree_left, int tree_right, int pos, int new_value, int oper) {
        if (tree_left == tree_right) {
            tree[index] = new_value;
            return;
        }
        int tree_middle = (tree_left + tree_right) / 2;
        if (pos <= tree_middle) {
            update(index * 2, tree_left, tree_middle, pos, new_value, oper ^ 1);
        }
        else {
            update(index * 2 + 1, tree_middle + 1, tree_right, pos, new_value, oper ^ 1);
        }

        if (oper == 0) tree[index] = tree[index * 2] | tree[index * 2 + 1];
        else tree[index] = tree[index * 2] ^ tree[index * 2 + 1];
    }

public:
    explicit SegmentTree(std::vector<int>& vec, int power) : pow(power) {
        n = vec.size();
        tree.resize(n * 4);
        build(vec, 1, 0, n - 1, (power + 1) % 2);
    }

    int ans(int pos, int val) {
        set(pos, val);
        return tree[1];
    }

    void set(int pos, int val) {
        update(1, 0, n - 1, pos, val, (pow + 1) % 2);
    }
};


signed main() {
    // freopen("sum.in", "r", stdin);
    // freopen("sum.out", "w", stdout);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> v(1 << n);
    for (int i = 0; i < 1 << n; ++i) std::cin >> v[i];

    SegmentTree T = SegmentTree(v, n);

    while (q--) {
        int a, b;
        std::cin >> a >> b;
        std::cout << T.ans(a - 1, b) << std::endl;
    }
}