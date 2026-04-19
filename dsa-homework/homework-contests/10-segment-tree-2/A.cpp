#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <iterator>

using namespace std;
#define int long long

class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;
    const int INF = LLONG_MAX;

    void build(std::vector<int>& vec, int index, int left, int right) {
        if (left == right) {
            tree[index] = vec[left];
        }
        else {
            int middle = (left + right) / 2;
            build(vec, index * 2, left, middle);
            build(vec, index * 2 + 1, middle + 1, right);
            tree[index] = std::min(tree[index * 2], tree[index * 2 + 1]);
        }
    }

    int query(int index, int tree_left, int tree_right, int left, int right) {
        if (left > right) return INF;
        if (tree_left == left && tree_right == right) return tree[index];

        int tree_middle = (tree_left + tree_right) / 2;
        return std::min(
                query(index * 2, tree_left, tree_middle, left, std::min(right, tree_middle)),
                query(index * 2 + 1, tree_middle + 1, tree_right, std::max(left, tree_middle + 1), right)
        );
    }

    void update(int index, int tree_left, int tree_right, int pos, int new_value) {
        if (tree_left == tree_right) {
            tree[index] = new_value;
        }
        else {
            int tree_middle = (tree_left + tree_right) / 2;
            if (pos <= tree_middle) {
                update(index * 2, tree_left, tree_middle, pos, new_value);
            }
            else {
                update(index * 2 + 1, tree_middle + 1, tree_right, pos, new_value);
            }
            tree[index] = std::min(tree[index * 2], tree[index * 2 + 1]);
        }
    }

public:
    explicit SegmentTree(std::vector<int>& vec) {
        n = vec.size();
        tree.resize(n * 4, INF);
        build(vec, 1, 0, n - 1);
    }

    int min(int l, int r) {
        return query(1, 0, n - 1, l, r);
    }

    void set(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }
};

signed main() {
    freopen("stupid_rmq.in", "r", stdin);
    freopen("stupid_rmq.out", "w", stdout);

    int n, q;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::cin >> q;

    SegmentTree T = SegmentTree(a);
    while (q--) {
        int left, right;
        std::cin >> left >> right;

        int answer = T.min(left - 1, right - 1);
        std::cout << answer << std::endl;
    }
}