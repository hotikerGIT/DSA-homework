#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>

struct Node {
    bool is_terminal = false;
    int prefix_cnt = 0;
    std::vector<Node*> alpha;
    Node* nxt = nullptr;
    char c = -1;

    Node() : alpha(26, nullptr) {}
};

class Trie {
public:
    Node* root = new Node();

    void add_word(const std::string& word) {
        if (has_word(word)) return;

        Node* current_node = root;
        current_node->prefix_cnt++;

        Node* prev_node;

        for (char c : word) {
            if (!current_node->alpha[c - 'a']) {
                current_node->alpha[c - 'a'] = new Node();
            }

            prev_node = current_node;
            current_node = current_node->alpha[c - 'a'];
            current_node->prefix_cnt++;
            prev_node->nxt = current_node;
            prev_node->c = c;
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

    std::string starts_with(const std::string& prefix) {
        Node* current_node = root;
        std::string res = prefix;

        for (char c : prefix) {
            if (current_node->alpha[c - 'a']) return "";
            current_node = current_node->nxt;
        }

        while (current_node->nxt != nullptr) {
            res += current_node->c;
            current_node = current_node->nxt;
        }

        return res;
    }

    std::string starts_with(int i) {
        std::string s(1, i + 'a');
        return starts_with(s);
    }

    std::set<std::string> get_suf_pref(const std::string& word) {
        std::set<std::string> res;

        for (int size = 1; size <= word.size(); ++size) {
            auto p = starts_with(word);
            if (!p.empty()) res.insert(p);
        }

        return res;
    }

    std::string cut_to_suf(const std::string& p, const std::string& q) {
        int i = 0;
        for (; i < q.size(); ++i) {
            if (p.back() == q[i]) break;
        }

        return q.substr(i, q.size() - i);
    }
};

bool check_kids(Node* cur) {
    int cnt = 0;

    for (auto ptr : cur->alpha) {
        cnt += ptr ? 1 : 0;
    }

    if (cnt > 2) return false;

    for (auto ptr : cur->alpha) {
        if (ptr) return check_kids(ptr);
    }

    return true;
}

bool check_unique(Node* cur, std::set<char>& unique) {
    if (!cur) return true;

    if (unique.contains(cur->c)) return false;
    unique.insert(cur->c);
    return cur->nxt == nullptr || check_unique(cur->nxt, unique);
}

std::string procedure(std::string& good_string, const std::string& next_string, Trie& trie) {
    good_string += next_string;

    auto suf_pref = trie.get_suf_pref(next_string);

    if (suf_pref.empty()) return "";

    if (suf_pref.size() > 1) return "NO";

    auto q = *suf_pref.begin();
    auto q_suf = trie.cut_to_suf(next_string, q);

    return q_suf;
}

int main() {
    int n;
    std::cin >> n;
    auto T = Trie();

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        T.add_word(s);
    }

    for (auto ptr : T.root->alpha) {
        if (!ptr) continue;
        if (!check_kids(ptr)) {
            std::cout << "NO";
            return 0;
        }
    }

    for (auto ptr : T.root->alpha) {
        if (!ptr) continue;
        std::set<char> unq;
        if (!check_unique(ptr, unq)) {
            std::cout << "NO";
            return 0;
        }
    }

    std::map<int, Node*> ends;
    for (int i = 0; i < 26; ++i) {
        if (T.root->alpha[i]) ends[i] = T.root->alpha[i];
    }

    for (auto ptr : T.root->alpha) {
        if (!ptr) continue;

        char last_char = -1;
        while (ptr->nxt != nullptr) {
            last_char = ptr->c;
            ptr = ptr->nxt;
        }

        ends.erase(last_char - 'a');
    }

    std::string left_over, res;
    while (!ends.empty() || !left_over.empty()) {
        if (left_over == "NO") {
            std::cout << "NO";
            return 0;
        }

        if (!left_over.empty()) {
            left_over = procedure(res, left_over, T);
            continue;
        }

        left_over = procedure(res, T.starts_with(ends.begin()->first), T);
    }

    std::cout << res;
}