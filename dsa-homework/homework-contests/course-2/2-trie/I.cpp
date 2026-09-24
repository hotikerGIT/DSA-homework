#include <vector>
#include <iostream>
#define int long long

const int MAX_BIT = 30;

struct Node {
    int prefix_cnt = 0;
    Node* to0 = nullptr;
    Node* to1 = nullptr;
};

class Trie {
    Node* root = new Node();

public:
    void add_number(int number) {
        Node* current_node = root;
        current_node->prefix_cnt++;

        for (int bit = MAX_BIT; bit >= 0; --bit) {
            bool b = (number >> bit) & 1;
            Node*& nxt = b ? current_node->to1 : current_node->to0;
            if (!nxt) {
                nxt = new Node();
            }

            current_node = nxt;
            current_node->prefix_cnt++;
        }
    }

    int xor_more(int number, int k) {
        Node* current_node = root;
        int res = 0;

        for (int bit = MAX_BIT; bit >= 0; --bit) {
            if (!current_node) break;
            bool b = (number >> bit) & 1;
            int cur_bit = (k >> bit) & 1;

            Node* zero = b ? current_node->to1 : current_node->to0;
            Node* one  = b ? current_node->to0 : current_node->to1;

            if (bit == 0) {
                if (cur_bit == 0) res += current_node->prefix_cnt;
                else res += one ? one->prefix_cnt : 0;
                break;
            }

            if (cur_bit == 0) {
                res += one ? one->prefix_cnt : 0;
                current_node = zero;
            } else {
                current_node = one;
            }
        }

        return res;
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, k;
    std::cin >> n >> k;
    Trie T = Trie();

    std::vector<int> pref_xor(n + 1);
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        pref_xor[i + 1] = pref_xor[i] ^ a;
        T.add_number(pref_xor[i + 1]);
    }

    int res = 0;

    for (int i = 1; i <= n; ++i) {
        res += T.xor_more(pref_xor[i], k);
    }

    std::cout << res / 2 + T.xor_more(0, k);
}