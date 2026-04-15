#include <bits/stdc++.h>

struct Node {
    int key;
    int priority;
    int number;
    Node* left;
    Node* right;

    Node(int key, int priority, int number) : key(key), priority(priority), number(number), left(nullptr), right(nullptr) {}

    ~Node() {
        delete left;
        delete right;
    }
};

int get_number(Node* root) {
    return root ? root->number : 0;
}

std::pair<Node*, Node*> split(Node* root, int key) {
    if (!root) return {nullptr, nullptr};

    if (root->key < key) {
        auto [L, R] = split(root->right, key);
        root->right = L;
        return {root, R};
    } else {
        auto [L, R] = split(root->left, key);
        root->left = R;
        return {L, root};
    }
}

Node* merge(Node* L, Node* R) {
    if (!L) return R;
    if (!R) return L;

    if (L->priority < R->priority) {
        L->right = merge(L->right, R);
        return L;
    } else {
        R->left = merge(L, R->left);
        return R;
    }
}

Node* insert(Node* root, int key, int priority, int number) {
    auto [L, R] = split(root, key);
    Node* newNode = new Node(key, priority, number);
    return merge(merge(L, newNode), R);
}

Node* erase(Node* root, int key) {
    auto [L, M] = split(root, key);
    auto [Mdel, R] = split(M, key + 1);
    delete Mdel;
    return merge(L, R);
}

bool find(Node* root, int key) {
    if (!root) return false;
    if (root->key == key) return true;
    if (key < root->key) return find(root->left, key);
    else return find(root->right, key);
}

struct Answer {
    int number, ancestor, left, right;

    bool operator<(const Answer other) const {
        return number < other.number;
    }
};

void fill(std::set<Answer>& out, Node* current, int previous) {
    if (!current) return;
    auto tmp = Answer(current->number, previous, get_number(current->left), get_number(current->right));
    out.insert(tmp);
    fill(out, current->left, current->number);
    fill(out, current->right, current->number);
}

int main() {
    int n;
    std::cin >> n;
    Node* tree = nullptr;

    for (int i = 1; i <= n; ++i) {
        int a, b;
        std::cin >> a >> b;
        tree = insert(tree, a, b, i);
    }

    std::cout << "YES\n";
    std::set<Answer> out;
    fill(out, tree, 0);
    for (auto ans : out) {
        std::cout << ans.ancestor << ' ' << ans.left << ' ' << ans.right << '\n';
    }

    return 0;
}