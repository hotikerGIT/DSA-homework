#include <iostream>
#include <vector>
#include <algorithm>

const int BLOCK_SIZE = 450;
std::vector<int> process(1e6 + 5, 0);
int ans = 0;

struct Query {
    int left, right, index, block_index;

    Query(int l, int r, int idx) : left(l), right(r), index(idx), block_index(l / BLOCK_SIZE) {}

    bool operator<(const Query& other) const {
        if (block_index != other.block_index) return block_index < other.block_index;
        return right < other.right;
    }
};

void add(int num) {
    if (process[num] == num) ans--;
    process[num]++;
    if (process[num] == num) ans++;
}

void remove(int num) {
    if (process[num] == num) ans--;
    process[num]--;
    if (process[num] == num) ans++;
}

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::vector<Query> queries;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, i);
    }

    std::sort(queries.begin(), queries.end());
    std::vector<int> answers(q);
    int cur_l = 0; int cur_r = -1;
    for (auto& query : queries) {
        while (cur_r < query.right) {
            ++cur_r;
            add(a[cur_r]);
        }
        while (cur_r > query.right) {
            remove(a[cur_r]);
            --cur_r;
        }
        while (cur_l < query.left) {
            remove(a[cur_l]);
            ++cur_l;
        }
        while (cur_l > query.left) {
            --cur_l;
            add(a[cur_l]);
        }
        answers[query.index] = ans;
    }

    for (int num : answers) std::cout << num << '\n';
}