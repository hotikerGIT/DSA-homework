#include <string>
#include <vector>
#include <map>
#include <iostream>

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    std::vector<Node*> alpha;
    bool can_win = false;

    bool is_leaf() {
        for (auto ptr : alpha) {
            if (ptr) return false;
        }

        return true;
    }

    Node() : alpha(26, nullptr) {}
};

class Trie {

public:
    Node* root = new Node();
    void add_word(const std::string& word) {
        Node* current_node = root;
        current_node->prefix_cnt++;

        for (char c : word) {
            if (!current_node->alpha[c - 'a']) {
                current_node->alpha[c - 'a'] = new Node();
            }

            current_node = current_node->alpha[c - 'a'];
            current_node->prefix_cnt++;
        }

        current_node->is_terminal = true;
    }

    bool has_word(const std::string& word) {
        Node* current_node = root;

        for (char c : word) {
            if (!current_node->alpha[c - 'a']) return false;
            current_node = current_node->alpha[c - 'a'];
        }

        return current_node->is_terminal;
    }

    int starts_with(const std::string& prefix) {
        Node* current_node = root;

        for (char c : prefix) {
            if (!current_node->alpha[c - 'a']) return false;
            current_node = current_node->alpha[c - 'a'];
        }

        return current_node->prefix_cnt;
    }

    void delete_word(const std::string& word) {
        if (!has_word(word)) return;

        Node* current_node = root;
        current_node->prefix_cnt--;

        for (char c : word) {
            current_node = current_node->alpha[c - 'a'];
            current_node->prefix_cnt--;
        }

        current_node->is_terminal = false;
    }
};

void dfs(Trie& trie, Node* cur) {
    if (cur->is_leaf()) {
        cur->can_win = true;
    }

    bool lose_child = false;
    for (Node* nxt : cur->alpha) {
        if (!nxt) continue;

        dfs(trie, nxt);

        if (!nxt->can_win) lose_child = true;
    }

    cur->can_win = lose_child;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    Trie win = Trie(), lose = Trie();
    for (int i = 0 ; i < n; ++i) {
        std::string s;
        std::cin >> s;
        win.add_word(s);
        lose.add_word(s.substr(0, s.size() - 1));
    }

    dfs(win, win.root);
    dfs(lose, lose.root);

    if (!win.root->can_win) {
        std::cout << "Second";
        return 0;
    }

    if (lose.root->can_win) {
        std::cout << "First";
        return 0;
    }

    std::cout << (k % 2 == 1 ? "First" : "Second");
}