#include <vector>
#include <iostream>

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    std::vector<Node*> alpha;

    Node() : alpha(2, nullptr) {}
};

class Trie {
    Node* root = new Node();

public:
    void add_number(int number) {
        Node* current_node = root;
        current_node->prefix_cnt++;

        for (int bit = 31; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            if (!current_node->alpha[b]) {
                current_node->alpha[b] = new Node();
            }

            current_node = current_node->alpha[b];
            current_node->prefix_cnt++;
        }

        current_node->is_terminal = true;
    }

    bool has_number(int number) {
        Node* current_node = root;

        for (int bit = 31; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            if (!current_node->alpha[b]) return false;

            current_node = current_node->alpha[b];
        }

        return current_node->is_terminal;
    }

    void delete_number(int number) {
        if (!has_number(number)) return;

        Node* current_node = root;
        current_node->prefix_cnt--;

        for (int bit = 31; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            current_node = current_node->alpha[b];
            current_node->prefix_cnt--;
        }

        current_node->is_terminal = current_node->prefix_cnt > 0;
    }

    int xor_max(int number) {
        Node* current_node = root;
        int res = 0;

        for (int bit = 31; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;

            int want = 1 - b;
            Node* next_node = current_node->alpha[want];
            if (next_node && next_node->prefix_cnt > 0) {
                res |= 1 << bit;
                current_node = next_node;
            } else {
                current_node = current_node->alpha[b];
            }
        }

        return res;
    }
};

int main() {
    int q;
    std::cin >> q;
    Trie T = Trie();
    T.add_number(0);

    for (int i = 0; i < q; ++i) {
        char type;
        int number;
        std::cin >> type >> number;

        if (type == '+') {
            T.add_number(number);
        }

        if (type == '-') {
            T.delete_number(number);
        }

        if (type == '?') {
            std::cout << T.xor_max(number) << '\n';
        }
    }
}