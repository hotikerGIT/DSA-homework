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

struct Query {
    int left;
    int right;
    int ans;
};

signed main() {
    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);

    const int NEUTRAL = (1ll << 31) - 1;

    int n, q;
    std::cin >> n >> q;
    vector<Query> queries;
    while (q--) {
        int i, j, m;
        std::cin >> i >> j >> m;
        queries.emplace_back(i, j, m);
    }

    // start[i] - ответ на запрос начинает содержать i
    // end[i] - ответ на запрос перестает содержать i
    vector<vector<int>> start(n + 1);
    vector<vector<int>> end(n + 1);

    for (auto& query : queries) {
        start[query.left].push_back(query.ans);
        end[query.right].push_back(query.ans);
    }

    vector<int> ans(n, NEUTRAL);
    multiset<int> query_max;

    // суммарно двойной цикл на самом деле сделает m + n итераций
    // при этом добавление произойдет m раз
    // в итоге получим n + m + mlogm
    for (int i = 0; i < n; ++i) {
        for (int num : start[i + 1]) {
            query_max.insert(num);
        }

        if (i > 0) {
            for (int num : end[i]) {
                query_max.erase(query_max.find(num));
            }
        }

        if (!query_max.empty()) ans[i] = *query_max.rbegin();
    }

    // получили вектор максимумов запросов
    // он будет искомым <=> поддерживает верный ответ на все запросы
    // для этого необходимо провести непосредственную проверку
    SegmentTree T = SegmentTree(ans);
    for (auto& query : queries) {
        int answer = T.min(query.left - 1, query.right - 1);
        if (query.ans != answer) {
            std::cout << "inconsistent" << '\n';
            return 0;
        }
    }

    std::cout << "consistent" << std::endl;
    for (int num : ans) {
        std::cout << num << ' ';
    }
}