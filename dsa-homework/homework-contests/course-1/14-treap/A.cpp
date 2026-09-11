#include <bits/stdc++.h>

std::mt19937 rnd(std::chrono::steady_clock::now().time_since_epoch().count());

struct Node {
    int value;
    int priority;
    int size;
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

std::pair<Node*, Node*> split(Node* root, int k) {
    if (!root) return {nullptr, nullptr};

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

int getValue(Node* root, int pos) {
    if (!root) return -1;

    int leftSize = getSize(root->left);
    if (pos == leftSize) {
        return root->value;
    } else if (pos < leftSize) {
        return getValue(root->left, pos);
    } else {
        return getValue(root->right, pos - leftSize - 1);
    }
}

Node* move(Node* root, int left, int right) {
    auto [L, R1] = split(root, left);
    auto [M, R] = split(R1, right - left + 1);
    return merge(merge(M, L), R);
}

void printTree(Node* root) {
    if (!root) return;
    printTree(root->left);
    std::cout << root->value << " ";
    printTree(root->right);
}

int main() {
    int n, q;
    std::cin >> n >> q;
    Node* tree = new Node(1);
    for (int i = 2; i <= n; ++i) {
        tree = insert(tree, i - 1, i);
    }

    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        tree = move(tree, l - 1, r - 1);
    }

    printTree(tree);
    delete tree;
}