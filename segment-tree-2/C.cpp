#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

#define int long long

const int BLOCK_SIZE = 250;
int N;

struct Element {
    int time, position, value;

    bool operator<(const Element& other) { return time < other.time; }
};

class ActiveTree {
private:
    std::vector<int> tree;
    int n = 0;

    int query(int index, int tree_left, int tree_right, int pos) {
        if (tree_left == tree_right) return tree_left;
        int tree_middle = (tree_left + tree_right) / 2;

        if (pos <= tree[index * 2]) return query(index * 2, tree_left, tree_middle, pos);
        else return query(index * 2 + 1, tree_middle + 1, tree_right, pos - tree[index * 2]);
    }

    void update(int index, int tree_left, int tree_right, int pos) {
        if (tree_left == tree_right) {
            tree[index] = 1;
            return;
        }

        int tree_middle = (tree_left + tree_right) / 2;
        if (pos <= tree_middle) update(index * 2, tree_left, tree_middle, pos);
        else update(index * 2 + 1, tree_middle + 1, tree_right, pos);

        tree[index] = tree[index * 2] + tree[index * 2 + 1];
    }

public:
    ActiveTree(int n) : n(n) { tree.resize(4 * n, 0); }
    int GetKthActive(int k) {
        return query(1, 0, n - 1, k);
    }

    void set(int pos) {
        update(1, 0, n - 1, pos);
    }
};

class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;
    ActiveTree active;
    std::vector<int> positions;
    int current_position = 0;
    const int INF = LLONG_MAX;

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
    explicit SegmentTree(std::vector<Element>& vec) : active(vec.size()) {
        n = vec.size();
        tree.resize(n * 4, INF);
        positions.resize(n);
        for (int i = 0; i < n; ++i) positions[i] = vec[i].position;
    }

    int min(int l, int r) {
        int ql = active.GetKthActive(l);
        int qr = active.GetKthActive(r);

        return query(1, 0, n - 1, ql, qr);
    }

    void set(int val) {
        int pos = positions[current_position];
        current_position++;
        active.set(pos);
        update(1, 0, n - 1, pos, val);
    }
};

struct Query {
    char command;
    int left, right, index;
};

struct Block {
    int size;
    // первый - индекс запроса, второй - само число
    std::list<std::pair<int, int>> content;

    Block() : size(0) {}

    void Insert(int pos, std::pair<int, int>& element) {
        auto it = content.begin();
        for (int i = 0; i < pos; ++i) ++it;
        content.insert(it, element);
        ++size;
    }

    [[nodiscard]] int GetSize() const {
        return size;
    }
};

// корнячка на листах потому что че бы и нет
std::vector<Element> GetVector(const std::vector<Query>& addition_queries) {
    std::list<Block> result;
    result.push_back(Block());

    for (auto& query : addition_queries) {
        int passed = 0;
        auto it = result.begin();
        std::pair<int, int> element = {query.index, query.right};

        while (it != result.end() && passed + it->size <= query.left) {
            passed += it->size;
            ++it;
        }

        if (it == result.end()) {
            --it;
            it->Insert(it->size, element);

        } else {
            it->Insert(query.left - passed, element);
        }

        if (it->size >= BLOCK_SIZE) {
            auto next_block_it = result.insert(std::next(it), Block());
            Block& next_block = *next_block_it;
            Block& current_block = *it;

            int mid = current_block.size / 2;
            auto split_it = current_block.content.begin();
            std::advance(split_it, mid);

            next_block.content.splice(next_block.content.begin(),
                                      current_block.content,
                                      split_it, current_block.content.end());

            next_block.size = next_block.content.size();
            current_block.size = current_block.content.size();
        }
    }

    std::vector<Element> out;
    out.reserve(N);

    for (auto& block : result) {
        for (auto& elem : block.content) {
            out.push_back({elem.first, (int)out.size(), elem.second});
        }
    }

    return out;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    freopen("rmq.in", "r", stdin);
    freopen("rmq.out", "w", stdout);

    int q;
    std::cin >> q;
    std::vector<Query> queries;
    std::vector<Query> addition;
    queries.reserve(q);
    addition.reserve(q);

    for (int i = 0; i < q; ++i) {
        char command;
        int left, right;
        std::cin >> command;
        std::cin >> left >> right;
        queries.emplace_back(command, left, right, i);

        if (command == '+') addition.emplace_back(command, left, right, i);
    }

    N = addition.size();
    auto result_vector = GetVector(addition);
    std::sort(result_vector.begin(), result_vector.end());

    SegmentTree T = SegmentTree(result_vector);
    for (auto& query : queries) {
        if (query.command == '+') T.set(query.right);
        else std::cout << T.min(query.left, query.right) << std::endl;
    }
}