#include <iostream>
#include <vector>
#define int long long
const int MOD = 1e9 + 7;

struct Matrix {
    int a00, a01, a10, a11;

    Matrix(int _a00, int _a01, int _a10, int _a11)
        : a00(_a00 % MOD), a01(_a01 % MOD), a10(_a10 % MOD), a11(_a11 % MOD) {}

    Matrix operator*(const Matrix& other) const {
        return {
            (a00 * other.a00 + a01 * other.a10) % MOD,
            (a00 * other.a01 + a01 * other.a11) % MOD,
            (a10 * other.a00 + a11 * other.a10) % MOD,
            (a10 * other.a01 + a11 * other.a11) % MOD
        };
    }

    bool is_zero() const {
        return a00 == 1 && a01 == 0 && a10 == 0 && a11 == 1;
    }
};

Matrix matrix_power(Matrix m, int power) {
    Matrix result(1, 0, 0, 1);
    while (power > 0) {
        if (power & 1) {
            result = result * m;
        }
        m = m * m;
        power >>= 1;
    }
    return result;
}

const Matrix FIB_MATRIX(0, 1, 1, 1);

struct Node {
    int prev_sum;
    int cur_sum;
    Matrix lazy;

    Node() : prev_sum(0), cur_sum(0), lazy(1, 0, 0, 1) {}

    Node(int val) : lazy(1, 0, 0, 1) {
        if (val == 0) {
            prev_sum = 0;
            cur_sum = 0;
        } else if (val == 1) {
            prev_sum = 0;
            cur_sum = 1;
        } else {
            Matrix res = matrix_power(FIB_MATRIX, val - 1);
            prev_sum = res.a10;
            cur_sum = res.a11;
        }
    }
};

class SegmentTree {
private:
    std::vector<Node> tree;
    int n;

    void apply(int index, const Matrix& M) {
        int new_prev = (tree[index].prev_sum * M.a00 + tree[index].cur_sum * M.a10) % MOD;
        int new_cur = (tree[index].prev_sum * M.a01 + tree[index].cur_sum * M.a11) % MOD;
        tree[index].prev_sum = new_prev;
        tree[index].cur_sum = new_cur;
    }

    void push(int index) {
        if (tree[index].lazy.is_zero()) return;

        apply(index, tree[index].lazy);

        if (index * 2 < (int)tree.size()) {
            tree[index * 2].lazy = tree[index * 2].lazy * tree[index].lazy;
            tree[index * 2 + 1].lazy = tree[index * 2 + 1].lazy * tree[index].lazy;
        }

        tree[index].lazy = Matrix(1, 0, 0, 1);
    }

    void build(int index, int tree_left, int tree_right, const std::vector<int>& vec) {
        if (tree_left == tree_right) {
            tree[index] = Node(vec[tree_left]);
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, vec);
        build(index * 2 + 1, tree_mid + 1, tree_right, vec);

        tree[index].prev_sum = (tree[index * 2].prev_sum + tree[index * 2 + 1].prev_sum) % MOD;
        tree[index].cur_sum = (tree[index * 2].cur_sum + tree[index * 2 + 1].cur_sum) % MOD;
    }

    void update(int index, int tree_left, int tree_right, int left, int right, const Matrix& M) {
        if (left <= tree_left && tree_right <= right) {
            tree[index].lazy = tree[index].lazy * M;
            push(index);
            return;
        }

        push(index);

        if (tree_right < left || right < tree_left) return;

        int tree_mid = (tree_left + tree_right) / 2;
        update(index * 2, tree_left, tree_mid, left, right, M);
        update(index * 2 + 1, tree_mid + 1, tree_right, left, right, M);

        push(index * 2);
        push(index * 2 + 1);
        tree[index].prev_sum = (tree[index * 2].prev_sum + tree[index * 2 + 1].prev_sum) % MOD;
        tree[index].cur_sum = (tree[index * 2].cur_sum + tree[index * 2 + 1].cur_sum) % MOD;
    }

    int query(int index, int tree_left, int tree_right, int left, int right) {
        push(index);

        if (left <= tree_left && tree_right <= right) {
            return tree[index].cur_sum % MOD;
        }

        if (tree_right < left || right < tree_left) return 0;

        int tree_mid = (tree_left + tree_right) / 2;
        return (query(index * 2, tree_left, tree_mid, left, right) +
                query(index * 2 + 1, tree_mid + 1, tree_right, left, right)) % MOD;
    }

public:
    SegmentTree(const std::vector<int>& vec) {
        n = vec.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, vec);
    }

    void add(int left, int right, int x) {
        if (x == 0) return;
        Matrix M = matrix_power(FIB_MATRIX, x);
        update(1, 0, n - 1, left, right, M);
    }

    int get_sum(int left, int right) {
        return query(1, 0, n - 1, left, right);
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }

    SegmentTree tree(a);

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        std::cin >> type >> l >> r;
        l--; r--;

        if (type == 1) {
            int x;
            std::cin >> x;
            tree.add(l, r, x);
        } else {
            std::cout << tree.get_sum(l, r) << '\n';
        }
    }

    return 0;
}