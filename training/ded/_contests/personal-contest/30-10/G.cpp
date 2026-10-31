#include <iostream>
#include <vector>
#include <algorithm>

struct Trie {
    struct Node {
        int cnt = 0;
        std::vector<int> next;

        Node(int cnt_) {
            cnt = cnt_;
            for (int& num : next) num = -1;
        }
    };

    std::vector<Node> nodes;

    void add_word(const std::string& word) {
        int cur = 0;

        for (char c : word) {
            int ind = c - 'a';

            if (nodes[cur].next[ind] == -1) {
                nodes[cur].next[ind] = nodes.size();
                nodes.emplace_back(0);
            }

            cur = nodes[cur].next[ind];
            nodes[cur].cnt++;
        }
    }
};

int main() {
    int n;
    std::cin >> n;
    auto T = Trie();
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        std::reverse(s.begin(), s.end());
        T.add_word(s);
    }

    int best = 0;
    int best_size = -1;
    auto dfs = [&](int cur, int len, auto&& self) {
        if (T.nodes[cur].cnt <= 1) return;

        if (len > best_size) {
            best = cur;
            best_size = len;
        }

        for (int next : T.nodes[cur].next) if (next != -1) self(next, len + 1, self);
    };
    dfs(0, 0, dfs);

    std::string res1, res2;
    auto get = [&](int cur, std::string& res, auto&& self) -> void {
        for (int i = 0; i < 26; ++i) {
            if (T.nodes[cur].next[i] != -1) {
                res += 'a' + i;
                self(T.nodes[cur].next[i], res, self);
                break;
            }
        }
    };

    auto restore = [&](int cur, bool& good, auto&& self) {
        if (cur == best) {
            good = true;

            bool got = false;
            for (int i = 0; i < 26; ++i) {
                int next = T.nodes[cur].next[i];

                if (next != -1) {
                    if (!got) {
                        res1 += 'a' + i;
                        get(next, res1, get);
                        got = true;
                    } else {
                        res2 += 'a' + i;
                        get(next, res2, get);
                        break;
                    }
                }
            }
        }

        if (good) {

        }
    };
}