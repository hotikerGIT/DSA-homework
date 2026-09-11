#include <iostream>
#include <vector>

// значение - количество свободных чисел на отрезке
class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;

    void build(int index, int left, int right) {
        if (left == right) {
            tree[index] = 1;  // первоначально все клетки свободны
            return;
        }

        int middle = (left + right) / 2;
        build(index * 2, left, middle);
        build(index * 2 + 1, middle + 1, right);
        tree[index] = tree[index * 2] + tree[index * 2 + 1];
    }

    // запрос возвращает первое свободное число после pos (>=)
    int query(int index, int tree_left, int tree_right, int pos) {
        if (tree_right < pos || tree[index] == 0) return -1;
        if (tree_left == tree_right) {
            return tree_left;
        }

        int tree_middle = (tree_left + tree_right) / 2;
        int left_val = query(index * 2, tree_left, tree_middle, pos);
        if (left_val != -1) return left_val;

        return query(index * 2 + 1, tree_middle + 1, tree_right, pos);
    }

    void update(int index, int tree_left, int tree_right, int pos, int new_value) {
        if (tree_left == tree_right) {
            tree[index] = new_value;
            return;
        }
        int tree_middle = (tree_left + tree_right) / 2;
        if (pos <= tree_middle) update(index * 2, tree_left, tree_middle, pos, new_value);
        else update(index * 2 + 1, tree_middle + 1, tree_right, pos, new_value);
        tree[index] = tree[index * 2] + tree[index * 2 + 1];
    }

public:
    explicit SegmentTree(int size) {
        n = size;
        tree.resize(n * 4, 0);
        build(1, 0, n - 1);
    }

    int place(int num) {
        int pos = query(1, 0, n - 1, num);
        update(1, 0, n - 1, pos, 0);
        return pos;
    }

    void remove(int num) {
        update(1, 0, n - 1, -num, 1);
    }

    std::vector<int>& check() {
        return tree;
    }
};

int main() {
    freopen("exam.in", "r", stdin);
    freopen("exam.out", "w", stdout);

    SegmentTree T = SegmentTree(2e5 + 8);
    int q;
    std::cin >> q;

    while (q--) {
        int num;
        std::cin >> num;

        if (num > 0) std::cout << T.place(num) << std::endl;
        else T.remove(num);
    }
}