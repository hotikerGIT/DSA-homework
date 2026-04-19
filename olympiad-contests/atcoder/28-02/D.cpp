#include <iostream>
#include <vector>
#include <string>
#define int long long

class SegmentTree {
private:
    std::vector<int> tree;
    int n = 0;

    // храним индекс самой первой единицы
    void build(std::vector<int> &vec, int index, int left, int right) {
        if (left == right) {
            tree[index] = vec[left] ? left :(int)1e9;
        } else {
            int middle = (left + right) / 2;
            build(vec, index * 2, left, middle);
            build(vec, index * 2 + 1, middle + 1, right);
            tree[index] = std::min(tree[index * 2], tree[index * 2 + 1]);
        }
    }

    int query(int index, int tree_left, int tree_right, int left, int right) {
        if (left <= tree_left && tree_right <= right) return tree[index];
        if (tree_right < left || right < tree_left) return 1e9;

        int tree_mid = (tree_left + tree_right) / 2;
        return std::min(query(index * 2, tree_left, tree_mid, left, right),
                        query(index * 2 + 1, tree_mid + 1, tree_right, left, right));
    }

    void update(int index, int tree_left, int tree_right, int pos, int new_value) {
        if (tree_left == tree_right) tree[index] = new_value;
        else {
            int tree_middle = (tree_left + tree_right) / 2;
            if (pos <= tree_middle) {
                update(index * 2, tree_left, tree_middle, pos, new_value);
            } else {
                update(index * 2 + 1, tree_middle + 1, tree_right, pos, new_value);
            }
            tree[index] = std::min(tree[index * 2], tree[index * 2 + 1]);
        }
    }

public:
    explicit SegmentTree(std::vector<int> &vec) {
        n = vec.size();
        tree.resize(n * 4);
        build(vec, 1, 0, n - 1);
    }

    int get_k(int l, int r) {
        if (r < l) return 1e9;

        int answer = query(1, 0, n - 1, l, r);
        if (answer < n) set(answer, 1e9);
        return answer;
    }

    void set(int pos, int val) {
        update(1, 0, n - 1, pos, val);
    }
};

signed main() {
    std::string s;
    std::cin >> s;
    int n = s.size();
    std::vector<int> a(n), b(n), c(n);
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'A') a[i] = 1;
        if (s[i] == 'B') b[i] = 1;
        if (s[i] == 'C') c[i] = 1;
    }

    SegmentTree TA(a), TB(b), TC(c);
    int answer = 0;

    while (true) {
        int index_a = TA.get_k(0, n - 1);
        if (index_a == 1e9) break;

        int index_b = TB.get_k(index_a, n - 1);
        if (index_b == 1e9) continue;

        int index_c = TC.get_k(index_b, n - 1);
        if (index_c == 1e9) continue;

        answer++;
    }

    std::cout << answer;
    return 0;
}