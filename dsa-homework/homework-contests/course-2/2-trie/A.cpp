#include <string>
#include <vector>
#include <map>
#include <iostream>

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    std::map<int, Node*> alpha;
};

class Trie {
    Node* root = new Node();

public:
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

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;
    Trie T = Trie();

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        T.add_word(s);
    }

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int type;
        std::string s;
        std::cin >> type >> s;

        if (type == 1) {
            T.add_word(s);
        }

        if (type == 2) {
            std::cout << T.starts_with(s) << '\n';
        }
    }
}