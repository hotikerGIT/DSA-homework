#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <functional>
#include <algorithm>

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
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    auto T = Trie();

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        T.add_word(s);
    }

    int res = 0;
    std::function<void(Node*)> dfs = [&](Node* cur) {
        if (cur->prefix_cnt <= k) {
            return;
        }

        for (auto ptr : cur->alpha) if (ptr) dfs(ptr);

        std::sort(cur->alpha.begin(), cur->alpha.end(), [&](Node* a, Node* b) {
            if (!a) return false;
            if (!b) return true;
            return a->prefix_cnt > b->prefix_cnt;
        });

        cur->prefix_cnt = cur->is_terminal;
        for (auto ptr : cur->alpha) if (ptr) cur->prefix_cnt += ptr->prefix_cnt;

        for (int i = 0; cur->prefix_cnt > k; ++i) {
            res++;
            cur->prefix_cnt -= cur->alpha[i]->prefix_cnt;
        }
    };

    dfs(T.root);
    std::cout << res + (T.root->prefix_cnt > 0);
}