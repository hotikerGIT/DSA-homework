#include <string>
#include <vector>
#include <iostream>
#include <set>
#include <map>

struct Node {
    bool is_terminal = false;
    std::vector<Node*> alpha;
    Node* nxt = nullptr;
    char c = -2;

    Node() : alpha(26, nullptr) {}
};

class Trie {
public:
    Node* root = new Node();

    void add_word(const std::string& word) {
        Node* current_node = root;

        Node* prev_node;

        for (char c : word) {
            if (!current_node->alpha[c - 'a']) {
                current_node->alpha[c - 'a'] = new Node();
            }

            prev_node = current_node;
            current_node = current_node->alpha[c - 'a'];
            prev_node->nxt = current_node;
            prev_node->c = c;
        }

        current_node->is_terminal = true;
    }
};

bool check_kids(Node* cur) {
    int cnt = 0;

    for (auto ptr : cur->alpha) {
        cnt += ptr ? 1 : 0;
    }

    if (cnt >= 2) return false;

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

bool get_symbols(Node* cur, char prev, std::map<char, std::pair<char, char>>& symbols) {
    if (!cur || cur->c < 0) return true;

    if (symbols[prev].second >= 0 && symbols[prev].second != cur->c) return false;
    if (symbols[cur->c].first >= 0 && symbols[cur->c].first != prev) return false;

    symbols[prev].second = cur->c;
    symbols[cur->c].first = prev;

    return get_symbols(cur->nxt, cur->c, symbols);
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

    std::map<char, std::pair<char, char>> symbols;

    for (int c = 0; c < 26; ++c) {
        if (!T.root->alpha[c]) {
            symbols[c + 'a'] = {-2, -2};
        } else {
            symbols[c + 'a'] = {-1, -1};
        }

    }

    for (int c = 0; c < 26; ++c) {
        if (!get_symbols(T.root->alpha[c], c + 'a', symbols)) {
            std::cout << "NO";
            return 0;
        }
    }

    std::set<char> starters;
    for (auto& [chr, pair] : symbols) {
        if (pair.first == -1) starters.insert(chr);
    }

    if (starters.empty()) {
        std::cout << "NO";
        return 0;
    }

    std::string res;
    std::set<char> used;
    for (auto c : starters) {
        res += c;
        used.insert(c);

        char nxt = symbols[c].second;
        while (nxt >= 'a' && nxt <= 'z') {
            if (used.contains(nxt)) {
                std::cout << "NO";
                return 0;
            }

            res += nxt;
            used.insert(nxt);
            nxt = symbols[nxt].second;
        }
    }

    int cnt = 0;
    for (auto& [chr, pair] : symbols) {
        if (pair.first != -2 || pair.second != -2) cnt++;
    }

    if (cnt != res.size()) {
        std::cout << "NO";
        return 0;
    }

    std::cout << res;
}