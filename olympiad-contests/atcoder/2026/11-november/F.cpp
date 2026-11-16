// clang-format off
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

#define int long long

using vi = vector<int>; using vvi = vector<vi>;
using pii = pair<int, int>; using vpii = vector<pii>;

using H = decltype([](uint64_t x) {
    static const uint64_t r = chrono::steady_clock::now().time_since_epoch().count();
    x += r + 0x9e3779b97f4a7c15ULL; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL; return x ^ (x >> 31);
});

template<class K, class V> using hash_map = __gnu_pbds::gp_hash_table<K, V, H>;
template<class K> using hash_set = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, H>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define nn '\n'

template <class T>
static int sz(const T& x) { return (int)size(x); }

template <class T, class U>
static bool chmin(T& a, const U& b) { return b < a ? (a = b, true) : false; }

template <class T, class U>
static bool chmax(T& a, const U& b) { return a < b ? (a = b, true) : false; }

template <class T>
void get_vector(vector<T>& a) {
    for (int i = 0; i < a.size(); ++i) std::cin >> a[i];
}

template <class T>
vector<T> read_vector(int size) {
    vector<T> res(size);
    for (int i = 0; i < res.size(); ++i) std::cin >> res[i];
    return res;
}

constexpr int INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 362880;

static void solve();

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) solve();
}
// clang-format on



struct Node {
    bool is_all_eq = true;
    int num = -1;
};

struct UpdateNode {
    int to_set = -10;

    bool operator==(const UpdateNode& other) const {
        bool is_equal = to_set == other.to_set;
        return is_equal;
    }
};

class SegmentTree {
private:
    std::vector<Node> tree;
    std::vector<UpdateNode> lazy;
    int n;

    Node Merge(const Node& node1, const Node& node2) {
        Node res;
        res.is_all_eq = true;
        res.num = -1;

        if (!node1.is_all_eq || !node2.is_all_eq) {
            res.is_all_eq = false;
        } else {
            if (node1.num == -1) {
                res.num = node2.num;
            } else if (node2.num == -1) {
                res.num = node1.num;
            } else if (node1.num == node2.num) {
                res.num = node1.num;
            } else {
                res.is_all_eq = false;
            }
        }

        return res;
    }

    void Compose(UpdateNode& node1, const UpdateNode& node2) {
        if (node2 == UpdateNode()) return;
        node1.to_set = node2.to_set;
    }

    void Update(Node& node, const UpdateNode& update_node) {
        if (update_node == UpdateNode()) return;

        node.is_all_eq = true;
        node.num = update_node.to_set;
    }

private:
    void build(int index, int tree_left, int tree_right, const std::vector<Node>& start) {
        if (tree_left == tree_right) {
            tree[index] = start[tree_left];
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, start);
        build(index * 2 + 1, tree_mid + 1, tree_right, start);
        tree[index] = Merge(tree[index * 2], tree[index * 2 + 1]);
    }

    Node get(int index, int tree_left, int tree_right, int left, int right) {
        push(index, tree_left, tree_right);

        if (left <= tree_left && tree_right <= right) return tree[index];
        if (right < tree_left || tree_right < left) return Node();

        int tree_mid = (tree_left + tree_right) / 2;
        return Merge(
                get(index * 2, tree_left, tree_mid, left, right),
                get(index * 2 + 1, tree_mid + 1, tree_right, left, right)
        );
    }

    void update(int index, int tree_left, int tree_right, int left, int right, UpdateNode& update_node) {
        if (left <= tree_left && tree_right <= right) {
            Compose(lazy[index], update_node);
            push(index, tree_left, tree_right);
            return;
        }

        push(index, tree_left, tree_right);

        if (right < tree_left || tree_right < left) return;

        int tree_mid = (tree_left + tree_right) / 2;
        update(index * 2, tree_left, tree_mid, left, right, update_node);
        update(index * 2 + 1, tree_mid + 1, tree_right, left, right, update_node);

        tree[index] = Merge(tree[index * 2], tree[index * 2 + 1]);
    }

    void push(int index, int tree_left, int tree_right) {
        Update(tree[index], lazy[index]);

        if (tree_left != tree_right) {
            Compose(lazy[index * 2], lazy[index]);
            Compose(lazy[index * 2 + 1], lazy[index]);
        }

        lazy[index] = UpdateNode();
    }

public:
    SegmentTree(const std::vector<Node>& start)
            : n(start.size()){
        tree.resize(4 * n, Node());
        lazy.resize(4 * n, UpdateNode());
        build(1, 0, n - 1, start);
    }

    void update(int left, int right, UpdateNode& update_node) {
        update(1, 0, n - 1, left, right, update_node);
    }

    Node get(int left, int right) {
        return get(1, 0, n - 1, left, right);
    }
};


void solve() {int n, query;
    std::cin >> n >> query;
    std::vector<Node> start_values(n);
    for (int i = 0; i < n; ++i) {
        int a;
        cin >> a;
        start_values[i] = Node(true, a);
    }

    SegmentTree T(start_values);

    for (int i = 0; i < query; ++i) {
        int type, a, b;
        cin >> type >> a >> b;

        if (type == 1) {
            UpdateNode updateNode = UpdateNode(b);
            T.update(a - 1, a - 1, updateNode);
        } else {
            auto node = T.get(a - 1, b - 1);
            cout << (node.is_all_eq ? "Yes" : "No") << nn;
        }
    }

}