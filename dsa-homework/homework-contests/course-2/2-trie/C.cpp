#include <string>
#include <vector>
#include <map>
#include <iostream>

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    std::vector<Node*> alpha;

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

    Node* move(Node* cur, char c) {
        if (!cur->alpha[c - 'a']) cur->alpha[c - 'a'] = new Node();

        return cur->alpha[c - 'a'];
    }

    int compute_size(Node* cur) {
        if (!cur) return 0;
        int res = 1;
        for (auto ptr : cur->alpha) {
            res += compute_size(ptr);
        }

        return res;
    }

    int compute_size() {
        return compute_size(root) - 1;
    }
};

int main() {
    std::string s;
    std::cin >> s;
    std::vector<bool> ban(26);
    for (int i = 0; i < 26; ++i) {
        char bit;
        std::cin >> bit;
        ban[i] = 1 - (bit - '0');
    }
    int k;
    std::cin >> k;

    Trie T = Trie();

    for (int left = 0; left < s.size(); ++left) {
        Node* current_node = T.root;
        int cur_price = 0;

        for (int right = left; right < s.size(); ++right) {
            cur_price += ban[s[right] - 'a'];

            if (cur_price > k) break;
            current_node = T.move(current_node, s[right]);
        }
    }

    std::cout << T.compute_size();
}