#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int value;
    int priority;
    int size;
    bool push = false;
    Node* left;
    Node* right;

    Node(int value) : value(value), priority(rnd()), size(1), left(nullptr), right(nullptr) {}
};

int getSize(Node* root) {
    return root ? root->size : 0;
}

void updateSize(Node* root) {
    if (root) {
        root->size = 1 + getSize(root->left) + getSize(root->right);
    }
}

void switchFlag(Node* root) {
    if (!root) return;
    root->push ^= 1;
}


void push(Node* root) {
    if (!root || !root->push) return;
    std::swap(root->left, root->right);

    switchFlag(root->left);
    switchFlag(root->right);
    root->push = false;
}

std::pair<Node*, Node*> split(Node* root, int k) {
    if (!root) return {nullptr, nullptr};
    push(root);

    if (getSize(root->left) >= k) {
        auto [L, R] = split(root->left, k);
        root->left = R;
        updateSize(root);
        return {L, root};
    } else {
        int leftSize = getSize(root->left);
        auto [L, R] = split(root->right, k - leftSize - 1);
        root->right = L;
        updateSize(root);
        return {root, R};
    }
}

Node* merge(Node* L, Node* R) {
    push(L);
    push(R);

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

Node* insert(Node* root, int pos, int value) {
    auto [L, R] = split(root, pos);
    Node* newNode = new Node(value);
    return merge(merge(L, newNode), R);
}

Node* erase(Node* root, int pos) {
    auto [L, M] = split(root, pos);
    auto [ToDel, R] = split(M, 1);
    delete ToDel;
    return merge(L, R);
}

Node* reverse(Node* root, int l, int r) {
    auto [L, R1] = split(root, l);
    auto [M, R] = split(R1, r - l + 1);
    switchFlag(M);
    return merge(merge(L, M), R);
}

Node* cycle(Node* root, int l, int r) {
    auto [L, R1] = split(root, l);
    auto [M, R2] = split(R1, r - l);
    auto [K, R] = split(R2, 1);
    return merge(merge(merge(L, K), M), R);
}

int getValue(Node* root, int pos) {
    if (!root) return -1;
    push(root);

    int leftSize = getSize(root->left);
    if (pos == leftSize) {
        return root->value;
    } else if (pos < leftSize) {
        return getValue(root->left, pos);
    } else {
        return getValue(root->right, pos - leftSize - 1);
    }
}

int main() {
    int n, q, m;
    std::cin >> n >> q >> m;
    Node* tree = nullptr;
    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        tree = insert(tree, i, num);
    }

    for (int i = 0; i < q; ++i) {
        int type, l, r;
        std::cin >> type >> l >> r;
        l--; r--;

        if (type == 1) {
            tree = cycle(tree, l, r);
        } else {
            tree = reverse(tree, l, r);
        }
    }

    for (int i = 0; i < m; ++i) {
        int p;
        std::cin >> p;
        p--;
        std::cout << getValue(tree, p) << ' ';
    }
}