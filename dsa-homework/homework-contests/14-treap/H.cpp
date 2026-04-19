#include <iostream>
#include <vector>
#include <random>
#include <chrono>
using namespace std;

#define int long long

static char mem_pool[240 << 20];
static size_t mem_ptr = 0;

void* operator new(size_t size) {
    size = (size + 7) & ~7;
    void* ptr = mem_pool + mem_ptr;
    mem_ptr += size;
    return ptr;
}

void operator delete(void*) noexcept {}

static uint64_t sm_state = (uint64_t)chrono::steady_clock::now().time_since_epoch().count();

uint64_t rnd() {
    sm_state ^= sm_state >> 12;
    sm_state ^= sm_state << 25;
    sm_state ^= sm_state >> 27;
    return sm_state * 0x2545F4914F6CDD1DULL;
}

struct Node {
    int key;
    int priority;
    int sum;
    int size;
    int count;
    Node* left;
    Node* right;

    Node(int key) : key(key), priority(rnd()), sum(key), size(1), count(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* root) {
    return root ? root->size : 0;
}

int getSum(Node* root) {
    return root ? root->sum : 0;
}

void updateSize(Node* root) {
    if (root) {
        root->size = root->count + getSize(root->left) + getSize(root->right);
        root->sum = root->key * root->count + getSum(root->left) + getSum(root->right);
    }
}

pair<Node*, Node*> split(Node* root, int key) {
    if (!root) return {nullptr, nullptr};

    if (root->key < key) {
        auto [L, R] = split(root->right, key);
        root->right = L;
        updateSize(root);
        return {root, R};
    } else {
        auto [L, R] = split(root->left, key);
        root->left = R;
        updateSize(root);
        return {L, root};
    }
}

pair<Node*, Node*> split_eq(Node* root, int key) {
    if (!root) return {nullptr, nullptr};

    if (root->key <= key) {
        auto [L, R] = split_eq(root->right, key);
        root->right = L;
        updateSize(root);
        return {root, R};
    } else {
        auto [L, R] = split_eq(root->left, key);
        root->left = R;
        updateSize(root);
        return {L, root};
    }
}

Node* merge(Node* L, Node* R) {
    if (!L) return R;
    if (!R) return L;

    if (L->priority > R->priority) {
        L->right = merge(L->right, R);
        updateSize(L);
        return L;
    } else {
        R->left = merge(L, R->left);
        updateSize(R);
        return R;
    }
}

Node* insert(Node* root, int key) {
    auto [L_eq, R_eq] = split_eq(root, key - 1);
    auto [M, R_final] = split(R_eq, key + 1);

    if (M) {
        M->count++;
        updateSize(M);
        return merge(merge(L_eq, M), R_final);
    }

    Node* newNode = new Node(key);
    return merge(merge(L_eq, newNode), R_final);
}

Node* erase(Node* root, int key) {
    auto [L, M] = split(root, key);
    auto [Mdel, R] = split(M, key + 1);

    if (Mdel) {
        if (Mdel->count > 1) {
            Mdel->count--;
            updateSize(Mdel);
            return merge(merge(L, Mdel), R);
        }
        delete Mdel;
    }
    return merge(L, R);
}

void find_less(Node* root, int x, int& cnt, int& sum) {
    Node* cur = root;
    while (cur) {
        if (cur->key < x) {
            cnt += getSize(cur->left) + cur->count;
            sum += getSum(cur->left) + cur->key * cur->count;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
}

void find_less_eq(Node* root, int x, int& cnt, int& sum) {
    Node* cur = root;
    while (cur) {
        if (cur->key <= x) {
            cnt += getSize(cur->left) + cur->count;
            sum += getSum(cur->left) + cur->key * cur->count;
            cur = cur->right;
        } else {
            cur = cur->left;
        }
    }
}

class SegmentTree {
private:
    vector<Node*> tree;
    vector<int> values;
    int n;

    void build(int index, int l, int r, const vector<int>& vec) {
        if (l == r) {
            tree[index] = new Node(vec[l]);
            return;
        }
        int m = (l + r) >> 1;
        build(index << 1, l, m, vec);
        build((index << 1) | 1, m + 1, r, vec);

        Node* left_tree = tree[index << 1];
        Node* right_tree = tree[(index << 1) | 1];

        vector<Node*> nodes;

        function<void(Node*)> collect = [&](Node* node) {
            if (!node) return;
            collect(node->left);
            nodes.push_back(node);
            collect(node->right);
        };

        collect(left_tree);
        collect(right_tree);

        for (auto node : nodes) {
            node->left = node->right = nullptr;
            updateSize(node);
        }

        Node* result = nullptr;
        for (auto node : nodes) {
            result = merge(result, node);
        }
        tree[index] = result;
    }

    void get_less(int index, int l, int r, int ql, int qr, int x, int& cnt, int& sum) {
        if (ql <= l && r <= qr) {
            find_less(tree[index], x, cnt, sum);
            return;
        }
        if (r < ql || l > qr) return;
        int m = (l + r) >> 1;
        if (ql <= m) get_less(index << 1, l, m, ql, qr, x, cnt, sum);
        if (qr > m) get_less((index << 1) | 1, m + 1, r, ql, qr, x, cnt, sum);
    }

    void get_less_eq(int index, int l, int r, int ql, int qr, int x, int& cnt, int& sum) {
        if (ql <= l && r <= qr) {
            find_less_eq(tree[index], x, cnt, sum);
            return;
        }
        if (r < ql || l > qr) return;
        int m = (l + r) >> 1;
        if (ql <= m) get_less_eq(index << 1, l, m, ql, qr, x, cnt, sum);
        if (qr > m) get_less_eq((index << 1) | 1, m + 1, r, ql, qr, x, cnt, sum);
    }

    void update(int index, int l, int r, int pos, int old_val, int new_val) {
        tree[index] = erase(tree[index], old_val);
        tree[index] = insert(tree[index], new_val);
        if (l == r) return;
        int m = (l + r) >> 1;
        if (pos <= m) update(index << 1, l, m, pos, old_val, new_val);
        else update((index << 1) | 1, m + 1, r, pos, old_val, new_val);
    }

public:
    SegmentTree(const vector<int>& vec) {
        n = vec.size();
        tree.resize(4 * n, nullptr);
        values = vec;
        build(1, 0, n - 1, vec);
    }

    void set(int pos, int x) {
        int old_val = values[pos];
        if (old_val == x) return;
        update(1, 0, n - 1, pos, old_val, x);
        values[pos] = x;
    }

    int out(int left, int right, int k) {
        if (k == 0) return 0;
        int bottom = -2000000000;
        int top = 2000000000;
        int ans = bottom;
        while (bottom <= top) {
            int mid = bottom + (top - bottom) / 2;
            int cnt = 0, sum = 0;
            get_less(1, 0, n - 1, left, right, mid, cnt, sum);
            if (cnt < k) {
                ans = mid;
                bottom = mid + 1;
            } else {
                top = mid - 1;
            }
        }
        int less_cnt = 0, less_sum = 0;
        get_less(1, 0, n - 1, left, right, ans, less_cnt, less_sum);
        int less_eq_cnt = 0, less_eq_sum = 0;
        get_less_eq(1, 0, n - 1, left, right, ans, less_eq_cnt, less_eq_sum);
        return less_sum + ans * (k - less_cnt);
    }
};

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    SegmentTree T(a);
    cin >> q;
    while (q--) {
        int type;
        cin >> type;
        if (type == 1) {
            int l, r, k;
            cin >> l >> r >> k;
            cout << T.out(l - 1, r - 1, k) << '\n';
        } else {
            int pos, x;
            cin >> pos >> x;
            T.set(pos - 1, x);
        }
    }
    return 0;
}