#include <iostream>
#include <vector>
#define int long long

class FenwickTree {
private:
    int n;
    std::vector<int> tree;

    int get(int index) {
        int res = 0;

        while (index >= 0) {
            res += tree[index];
            index = (index & (index + 1)) - 1;
        }

        return res;
    }

    void update(int index, int delta) {
        while (index < n) {
            tree[index] += delta;
            index = index | (index + 1);
        }
    }

public:
    FenwickTree(const std::vector<int>& vec) : n(vec.size()), tree(n) {
        for (int i = 0; i < n; ++i) {
            tree[i] += vec[i];

            int j = i | (i + 1);
            if (j < n) tree[j] += tree[i];
        }
    }

    int out(int left, int right) {
        if (left == 0) return get(right);
        return get(right) - get(left - 1);
    }

    void set(int pos, int val) {
        int current = out(pos, pos);
        update(pos, val - current);
    }
};

signed main() {
    freopen("rsq.in", "r", stdin);
    freopen("rsq.out", "w", stdout);

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    FenwickTree T(a);

    for (int i = 0; i < q; ++i) {
        int type, x, y;
        std::cin >> type >> x >> y;

        if (type == 0) std::cout << T.out(x - 1, y - 1) << '\n';
        else T.set(x - 1, y);
    }

    return 0;
}