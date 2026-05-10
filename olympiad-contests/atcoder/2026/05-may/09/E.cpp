#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

struct Node {
    std::map<int, int> labelCount;
    bool hasDuplicate;

    Node() {
        hasDuplicate = false;
    }

    Node(const std::map<int, int>& marks) {
        labelCount = marks;
        for (auto& [a, b]: marks)
        hasDuplicate |= b > 1;
    }
};

class SegmentTree {
private:
    int n;
    std::vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node result;
        result.labelCount = left.labelCount;

        for (const auto& [label, count] : right.labelCount) {
            result.labelCount[label] += count;
        }

        result.hasDuplicate = left.hasDuplicate || right.hasDuplicate;

        for (const auto& [label, count] : result.labelCount) {
            if (count > 1) result.hasDuplicate = true;
        }

        return result;
    }

    void build(int v, int tl, int tr, const std::vector<std::map<int, int>>& marks) {
        if (tl == tr) {
            tree[v] = Node(marks[tl]);
            return;
        }

        int tm = (tl + tr) / 2;
        build(v * 2, tl, tm, marks);
        build(v * 2 + 1, tm + 1, tr, marks);
        tree[v] = merge(tree[v * 2], tree[v * 2 + 1]);
    }

    Node queryDuplicate(int v, int tl, int tr, int l, int r) {
        if (tr < l || r < tl) return {};
        if (l <= tl && tr <= r) {
            return tree[v];
        }

        int tm = (tl + tr) / 2;
        return merge(queryDuplicate(v, tl, tm, l, r), queryDuplicate(v, tm + 1, tr, l, r));
    }

public:
    SegmentTree(const std::vector<std::map<int, int>>& marks) {
        n = marks.size();
        tree.resize(4 * n);
        build(1, 0, n - 1, marks);
    }

    bool hasDuplicate(int l, int r) {
        return queryDuplicate(1, 0, n - 1, l, r).hasDuplicate;
    }
};

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::pair<int, int>> intervals(m);
    std::vector<std::vector<int>> left(n + 1), right(n + 1);
    std::vector<std::map<int, int>> marks(n + 1);

    for (int i = 0; i < m; ++i) {
        int a, b;
        std::cin >> a >> b;
        intervals[i] = {a, b};
        left[a].push_back(b);
        right[b].push_back(a);
        marks[a][i]++;
        marks[b][i]++;
    }
    SegmentTree T(marks);

    for (int i = 0; i <= n; ++i) {
        std::sort(left[i].begin(), left[i].end());
        std::sort(right[i].begin(), right[i].end());
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int s, t;
        std::cin >> s >> t;

        auto first_it = std::upper_bound(left[s].begin(), left[s].end(), t);
        auto second_it = std::lower_bound(right[t].begin(), right[t].end(), s);

        if (first_it == left[s].begin() || second_it == right[t].end()) {
            std::cout << "No\n";
            continue;
        }

        std::pair<int, int> first = {s, *(--first_it)}, second = {*second_it, t};

        if (first == second && !T.hasDuplicate(s, t)) {
            std::cout << "No\n";
            continue;
        }

        if (first.second < second.first) {
            std::cout << "No\n";
            continue;
        }

        std::cout << "Yes\n";
    }
}