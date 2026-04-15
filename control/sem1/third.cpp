#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

const int MOD = 1e9 + 7;
const int P = 31;
const int ALPHABET = 26;

struct Node {
    std::string s;
    int forward_hash;
    int inverse_hash;
    int length;
    std::vector<int> freq;

    Node() : s(""), forward_hash(0), inverse_hash(0), length(0), freq(ALPHABET, 0) {}

    Node(char c) {
        s = std::string(1, c);
        length = 1;
        freq.resize(ALPHABET, 0);
        freq[c - 'a'] = 1;

        forward_hash = c - 'a' + 1;
        inverse_hash = c - 'a' + 1;
    }

    long long pow_mod(long long a, long long b) {
        long long res = 1;
        while (b > 0) {
            if (b & 1) res = (res * a) % MOD;
            a = (a * a) % MOD;
            b >>= 1;
        }
        return res;
    }
};

Node combine(const Node& left, const Node& right) {
    Node result;

    result.s = left.s + right.s;
    result.length = left.length + right.length;

    result.freq.assign(ALPHABET, 0);
    for (int i = 0; i < ALPHABET; i++) {
        result.freq[i] = left.freq[i] + right.freq[i];
    }

    long long pow_right = 1;
    for (int i = 0; i < right.length; i++) {
        pow_right = (pow_right * P) % MOD;
    }
    result.forward_hash = ((long long)left.forward_hash * pow_right + right.forward_hash) % MOD;

    long long pow_left = 1;
    for (int i = 0; i < left.length; i++) {
        pow_left = (pow_left * P) % MOD;
    }
    result.inverse_hash = ((long long)right.inverse_hash * pow_left + left.inverse_hash) % MOD;

    return result;
}

class SegmentTree {
private:
    std::vector<Node> tree;
    std::string arr;
    int n;

    void build(int index, int left, int right) {
        if (left == right) {
            tree[index] = Node(arr[left]);
            return;
        }

        int mid = (left + right) / 2;
        build(index * 2, left, mid);
        build(index * 2 + 1, mid + 1, right);

        tree[index] = combine(tree[index * 2], tree[index * 2 + 1]);
    }

    Node query(int index, int left, int right, int ql, int qr) {
        if (ql > qr) return Node();
        if (left == ql && right == qr) {
            return tree[index];
        }

        int mid = (left + right) / 2;
        Node left_result = query(index * 2, left, mid, ql, std::min(qr, mid));
        Node right_result = query(index * 2 + 1, mid + 1, right, std::max(ql, mid + 1), qr);

        return combine(left_result, right_result);
    }

    void update(int index, int left, int right, int pos, char c) {
        if (left == right) {
            tree[index] = Node(c);
            arr[pos] = c;
            return;
        }

        int mid = (left + right) / 2;
        if (pos <= mid) {
            update(index * 2, left, mid, pos, c);
        } else {
            update(index * 2 + 1, mid + 1, right, pos, c);
        }

        tree[index] = combine(tree[index * 2], tree[index * 2 + 1]);
    }

public:
    SegmentTree(const std::string& s) {
        arr = s;
        n = s.length();
        tree.resize(4 * n);
        build(1, 0, n - 1);
    }

    std::string concat(int l1, int r1, int l2, int r2) {
        Node node1 = query(1, 0, n - 1, l1, r1);
        Node node2 = query(1, 0, n - 1, l2, r2);
        Node combined = combine(node1, node2);
        return combined.s;
    }

    void insert_most_frequent(int l, int r, int pos) {
        Node node = query(1, 0, n - 1, l, r);

        int max_freq = 0;
        char most_freq_char = 'a';
        for (int i = 0; i < ALPHABET; i++) {
            if (node.freq[i] > max_freq) {
                max_freq = node.freq[i];
                most_freq_char = 'a' + i;
            }
        }

        if (pos < n) {
            std::string left_part = query(1, 0, n - 1, 0, pos - 1).s;
            std::string right_part = query(1, 0, n - 1, pos, n - 1).s;

            std::string new_str = left_part + std::string(1, most_freq_char) + right_part;

            arr = new_str;
            n = arr.length();
            tree.resize(4 * n);
            build(1, 0, n - 1);
        } else {
            std::string new_str = arr + std::string(1, most_freq_char);
            arr = new_str;
            n = arr.length();
            tree.resize(4 * n);
            build(1, 0, n - 1);
        }
    }

    bool is_palindrome(int l, int r) {
        Node node = query(1, 0, n - 1, l, r);
        return node.forward_hash == node.inverse_hash;
    }

    bool can_be_palindrome(int l, int r) {
        Node node = query(1, 0, n - 1, l, r);

        int odd_count = 0;
        for (int i = 0; i < ALPHABET; i++) {
            if (node.freq[i] % 2 == 1) {
                odd_count++;
            }
        }

        return odd_count <= 1;
    }

    std::string get_substring(int l, int r) {
        return query(1, 0, n - 1, l, r).s;
    }

    std::string get_string() {
        return arr;
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;
    std::string s;
    std::cin >> s;

    SegmentTree st(s);

    bool flag_given_answer = false;
    std::string candidate;
    for (int i = 0; i < q; i++) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l1, r1, l2, r2;
            std::cin >> l1 >> r1 >> l2 >> r2;
            l1--; r1--; l2--; r2--;

            std::string result = st.concat(l1, r1, l2, r2);

            Node combined_node;
            for (char c : result) {
                combined_node = combine(combined_node, Node(c));
            }

            if (combined_node.forward_hash == combined_node.inverse_hash) {
                if (!flag_given_answer) {
                    std::cout << result << std::endl;
                    flag_given_answer = true;
                }

            }
            else {
                int odd_count = 0;
                for (int j = 0; j < ALPHABET; j++) {
                    if (combined_node.freq[j] % 2 == 1) {
                        odd_count++;
                    }
                }

                if (odd_count <= 1) {
                    candidate = result;
                }

                else {
                    if (candidate.empty()) candidate = result;
                }
            }
        }

        else if (type == 2) {
            int l, r, pos;
            std::cin >> l >> r >> pos;
            l--; r--; pos--;

            st.insert_most_frequent(l, r, pos);
        }
    }

    if (flag_given_answer) return 0;
    std::cout << candidate;
}