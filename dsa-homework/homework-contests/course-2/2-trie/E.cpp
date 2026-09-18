#include <vector>
#include <iostream>

const int MAX_BIT = 20;

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    int cur_level = MAX_BIT + 1;
    std::vector<Node*> alpha;

    Node() : alpha(2, nullptr) {}
};

class Trie {
    Node* root = new Node();

public:
    void add_number(int number) {
        if (has_number(number)) return;

        Node* current_node = root;
        current_node->prefix_cnt++;

        for (int bit = MAX_BIT; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            if (!current_node->alpha[b]) {
                current_node->alpha[b] = new Node();
                current_node->alpha[b]->cur_level = bit;
            }

            current_node = current_node->alpha[b];
            current_node->prefix_cnt++;
        }

        current_node->is_terminal = true;
    }

    bool has_number(int number) {
        Node* current_node = root;

        for (int bit = MAX_BIT; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            if (!current_node->alpha[b]) return false;

            current_node = current_node->alpha[b];
        }

        return current_node->is_terminal;
    }

    int xor_mex(int number) {
        Node* current_node = root;
        int res = 0;

        for (int bit = MAX_BIT; bit >= 0; --bit) {
            if (!current_node) break;
            bool b = (number >> bit) & 1;

            Node* next_node = current_node->alpha[b];

            if (!next_node) break;

            if (next_node->prefix_cnt < (1 << next_node->cur_level)) {
                current_node = current_node->alpha[b];
            } else {
                res |= 1 << bit;
                current_node = current_node->alpha[1 - b];
            }
        }

        return res;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m, global_lazy = 0;
    std::cin >> n >> m;
    Trie T = Trie();

    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        T.add_number(a);
    }

    for (int i = 0; i < m; ++i) {
        int x;
        std::cin >> x;
        global_lazy ^= x;

        std::cout << T.xor_mex(global_lazy) << '\n';
    }
}