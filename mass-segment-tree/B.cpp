#include <iostream>
#include <vector>

int gcd(int a, int b) {
    if (a > b) std::swap(a, b);
    if (a == 0) return b;
    return gcd(b % a, a);
}

// вершина хранит гцд на отрезке
class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;
    int count_for_query = 0;

    void build(std::vector<int>& vec, int index, int left, int right) {
        if (left == right) {
            tree[index] = vec[left];
        }
        else {
            int middle = (left + right) / 2;
            build(vec, index * 2, left, middle);
            build(vec, index * 2 + 1, middle + 1, right);
            tree[index] = gcd(tree[index * 2], tree[index * 2 + 1]);
        }
    }

    void query(int index, int tree_left, int tree_right, int left, int right, int x) {
        if (count_for_query >= 2) return;
        if (left > right) return;
        if (tree_left == left && tree_right == right) {
            descend(index, tree_left, tree_right, x);
            return;
        }

        int tree_middle = (tree_left + tree_right) / 2;
        query(index * 2, tree_left, tree_middle, left, std::min(right, tree_middle), x);
        query(index * 2 + 1, tree_middle + 1, tree_right, std::max(left, tree_middle + 1), right, x);
    }

    // спуск по дереву с обновлением счетчика
    void descend(int index, int left, int right, int x) {
        if (count_for_query >= 2) return;
        if (tree[index] % x == 0) return;
        if (left == right) {
            count_for_query += tree[index] % x != 0;
            return;
        }

        if (tree[index * 2] % x && tree[index * 2 + 1] % x) {
            count_for_query = 2;
            return;
        }

        int mid = (left + right) / 2;
        descend(index * 2, left, mid, x);
        descend(index * 2 + 1, mid + 1, right, x);
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
            tree[index] = gcd(tree[index * 2], tree[index * 2 + 1]);
        }
    }

public:
    explicit SegmentTree(std::vector<int>& vec) {
        n = vec.size();
        tree.resize(n * 4, 0);
        build(vec, 1, 0, n - 1);
    }

    bool get(int l, int r, int x) {
        count_for_query = 0;
        query(1, 0, n - 1, l - 1, r - 1, x);
        if (count_for_query >= 2) return false;
        return true;
    }

    void set(int pos, int val) {
        update(1, 0, n - 1, pos - 1, val);
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    SegmentTree T = SegmentTree(a);
    int q;
    std::cin >> q;

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l, r, x;
            std::cin >> l >> r >> x;

            if (T.get(l, r, x)) std::cout << "YES\n";
            else std::cout << "NO\n";
        }

        else {
            int pos, y;
            std::cin >> pos >> y;

            T.set(pos, y);
        }
    }

    return 0;
}