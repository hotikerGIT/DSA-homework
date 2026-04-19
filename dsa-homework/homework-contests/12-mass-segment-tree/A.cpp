#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>
#include <cstdio>
#include <iterator>
#include <sstream>

using namespace std;
#define int long long

struct Node {
    int minimum;
    int difference;

    Node(int val) : minimum(val), difference(0) {}
};

class SegmentTree {
private:
    std::vector<Node> tree;
    int n = 0;
    const int INF = LLONG_MAX;

    void build(std::vector<int>& vec, int index, int left, int right) {
        if (left == right) {
            tree[index].minimum = vec[left];
        }
        else {
            int middle = (left + right) / 2;
            build(vec, index * 2, left, middle);
            build(vec, index * 2 + 1, middle + 1, right);
            tree[index].minimum = std::min(tree[index * 2].minimum, tree[index * 2 + 1].minimum);
        }
    }

    int query(int index, int tree_left, int tree_right, int left, int right) {
        push(index);

        if (left > right) return INF;
        if (tree_left >= left && tree_right <= right) return tree[index].minimum;

        int tree_middle = (tree_left + tree_right) / 2;
        return std::min(
            query(index * 2, tree_left, tree_middle, left, std::min(right, tree_middle)),
            query(index * 2 + 1, tree_middle + 1, tree_right, std::max(left, tree_middle + 1), right)
        );
    }

    void update(int index, int tree_left, int tree_right, int pos, int new_value) {
        push(index);

        if (tree_left == tree_right) {
            tree[index].minimum += new_value;
        }
        else {
            int tree_middle = (tree_left + tree_right) / 2;
            if (pos <= tree_middle) {
                update(index * 2, tree_left, tree_middle, pos, new_value);
            }
            else {
                update(index * 2 + 1, tree_middle + 1, tree_right, pos, new_value);
            }
            tree[index].minimum = std::min(tree[index * 2].minimum, tree[index * 2 + 1].minimum);
        }
    }

    void mass_update(int index, int tree_left, int tree_right, int left, int right, int value) {
        if (left <= tree_left && tree_right <= right) {
            tree[index].difference += value;
            push(index);
            return;
        }

        push(index);

        int tree_middle = (tree_left + tree_right) / 2;
        if (left <= tree_middle) {
            mass_update(index * 2, tree_left, tree_middle,
                       left, std::min(right, tree_middle), value);
        }
        if (right > tree_middle) {
            mass_update(index * 2 + 1, tree_middle + 1, tree_right,
                       std::max(left, tree_middle + 1), right, value);
        }

        tree[index].minimum = std::min(tree[index * 2].minimum,
                                      tree[index * 2 + 1].minimum);
    }

    void push(int index) {
        small_push(index);

        if (index * 2 + 1 < tree.size()) {
            small_push(index * 2);
            small_push(index * 2 + 1);
        }
    }

    void small_push(int index) {
        if (index > tree.size()) return;
        tree[index].minimum += tree[index].difference;

        if (index * 2 + 1 < tree.size()) {
            tree[index * 2].difference += tree[index].difference;
            tree[index * 2 + 1].difference += tree[index].difference;
        }

        tree[index].difference = 0;
    }

public:
    explicit SegmentTree(std::vector<int>& vec) {
        n = vec.size();
        tree.resize(n * 4, Node(INF));
        build(vec, 1, 0, n - 1);
    }

    int rmq(int lf, int rg) {
        if (lf <= rg) {
            return query(1, 0, n - 1, lf, rg);
        }

        return std::min(query(1, 0, n - 1, 0, rg), query(1, 0, n - 1, lf, n - 1));
    }

    void inc(int lf, int rg, int v) {
        if (lf <= rg) {
            mass_update(1, 0, n - 1, lf, rg, v);
        }

        else {
            mass_update(1, 0, n - 1, 0, rg, v);
            mass_update(1, 0, n - 1, lf, n - 1, v);
        }
    }
};

struct Query {
    int left;
    int right;
    int ans;
};

signed main() {
    int n;
    std::cin >> n;
    std::vector<int> arr(n);
    for (int i = 0; i < n; ++i) std::cin >> arr[i];
    int q;
    std::cin >> q;

    SegmentTree T = SegmentTree(arr);
    std::string dummy;
    std::getline(std::cin, dummy);

    for (int i = 0; i < q; ++i) {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream stream(line);

        int left, right, value;
        stream >> left >> right;

        if (stream >> value) {
            T.inc(left, right, value);
        }

        else {
            std::cout << T.rmq(left, right) << std::endl;
        }
    }

    return 0;
}