#include <iostream>
#include <vector>

struct Node {
    int size = 1, answer = 1;
    std::vector<int> orders = {1, 1, 1, 1};
    /*
     * 0 - увеличивается, начало = лево
     * 1 - увеличивается, конец = право
     * 2 - уменьшается, начало = лево
     * 3 - уменьшается, конец = право
     */

    int num_left, num_right;
    int difference = 0;
    bool touch_left, touch_right;

    Node() = default;

    void merge(Node& c1, Node& c2) {
        orders[0] = c1.orders[0];
        orders[1] = c2.orders[1];
        orders[2] = c1.orders[2];
        orders[3] = c2.orders[3];

        if (c2.orders[1] == c2.orders[0] && c1.num_right < c2.num_left) {
            orders[0] += c2.orders[0];
            orders[1] += c1.orders[1];
        }

        if (c1.orders[2] == c1.orders[3] && c1.num_right > c2.num_left) {
            orders[2] += c2.orders[2];
            orders[3] = c1.orders[3];
        }

        num_left = c1.num_left;
        num_right = c2.num_right;


    }
};

class SegmentTree {
    std::vector<Node> tree;
    int n;

    void build(int index, int tree_left, int tree_right, const std::vector<int>& vec) {
        if (tree_left == tree_right) {
            tree[index].num_left = vec[tree_left];
            tree[index].num_right = vec[tree_left];
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, vec);
        build(index * 2 + 1, tree_mid + 1, tree_right, vec);

        tree[index].size = tree_right - tree_left + 1;

    }
};