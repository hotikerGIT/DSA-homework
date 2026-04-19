#include <bits/stdc++.h>
#define int long long

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

const int P = 127;
const int MOD = 1e9 + 7;
const int MAXN = 3e5;

int powP[MAXN + 1];

void init_pow() {
    powP[0] = 1;
    for (int i = 1; i <= MAXN; ++i) {
        powP[i] = (powP[i - 1] * 1LL * P) % MOD;
    }
}

struct Node {
    int hash, reverse_hash;
    int priority;
    int size;
    Node* left;
    Node* right;
    char value;

    Node(char s)
            : value(s)
            , hash(s - 'a' + 1)
            , reverse_hash(s - 'a' + 1)
            , priority(rnd())
            , size(1)
            , left(nullptr)
            , right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

int getSize(Node* root) {
    return root ? root->size : 0;
}

int getHash(Node* root) {
    return root ? root->hash : 0;
}

int getReverseHash(Node* root) {
    return root ? root->reverse_hash : 0;
}

void update(Node* root) {
    if (!root) return;

    int leftSize = getSize(root->left);
    int rightSize = getSize(root->right);
    root->size = 1 + leftSize + rightSize;

    root->hash = (getHash(root->left) * 1LL * powP[1 + rightSize] +
                  (root->value - 'a' + 1) * 1LL * powP[rightSize] +
                  getHash(root->right)) % MOD;

    root->reverse_hash = (getReverseHash(root->right) * 1LL * powP[1 + leftSize] +
                          (root->value - 'a' + 1) * 1LL * powP[leftSize] +
                          getReverseHash(root->left)) % MOD;
}

std::pair<Node*, Node*> split(Node* root, int k) {
    if (!root) return {nullptr, nullptr};

    if (getSize(root->left) >= k) {
        auto [L, R] = split(root->left, k);
        root->left = R;
        update(root);
        return {L, root};
    } else {
        int leftSize = getSize(root->left);
        auto [L, R] = split(root->right, k - leftSize - 1);
        root->right = L;
        update(root);
        return {root, R};
    }
}

Node* merge(Node* L, Node* R) {
    if (!L) return R;
    if (!R) return L;

    if (L->priority > R->priority) {
        L->right = merge(L->right, R);
        update(L);
        return L;
    } else {
        R->left = merge(L, R->left);
        update(R);
        return R;
    }
}

Node* insert(Node* root, int pos, char c) {
    auto [L, R] = split(root, pos);
    Node* newNode = new Node(c);
    return merge(merge(L, newNode), R);
}

Node* erase(Node* root, int l, int r) {
    auto [L, L1] = split(root, l);
    auto [M, R] = split(L1, r - l + 1);
    delete M;
    return merge(L, R);
}

bool query(Node*& root, int l, int r) {
    auto [L, R1] = split(root, l);
    auto [M, R] = split(R1, r - l + 1);
    bool ans = false;
    if (M) {
        ans = (M->hash == M->reverse_hash);
    }
    root = merge(merge(L, M), R);
    return ans;
}

signed main() {
    init_pow();

    int n, q;
    std::cin >> n >> q;
    Node* tree = nullptr;
    std::string s;
    std::cin >> s;

    for (int i = 0; i < n; ++i) {
        tree = insert(tree, i, s[i]);
    }

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;
        if (type == 1) {
            int l, r;
            std::cin >> l >> r;
            tree = erase(tree, l - 1, r - 1);
        }
        else if (type == 2) {
            char c;
            int p;
            std::cin >> c >> p;
            tree = insert(tree, p - 1, c);
        }
        else {
            int l, r;
            std::cin >> l >> r;
            std::cout << (query(tree, l - 1, r - 1) ? "yes" : "no") << '\n';
        }
    }

    return 0;
}