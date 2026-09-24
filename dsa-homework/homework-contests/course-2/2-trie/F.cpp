#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct Node {
    int index = -1;
    int child = -1;
    int next = -1;
    char c = 0;
};

class Trie {
public:
    std::vector<Node> nodes;
    int root;

    Trie() {
        nodes.reserve(1);
        nodes.emplace_back();
        root = 0;
    }

    int find_child(int parent, char c) const {
        for (int v = nodes[parent].child; v != -1; v = nodes[v].next)
            if (nodes[v].c == c) return v;
        return -1;
    }

    int add_child(int parent, char c) {
        int id = (int)nodes.size();

        Node n;
        n.c = c;

        nodes.push_back(n);
        nodes[id].next = nodes[parent].child;
        nodes[parent].child = id;

        return id;
    }

    void add_word(const std::string& s, int start, int starting_index = 0, bool is_inverse = false) {
        int current = root;

        for (int i = start; i < (int)s.size(); ++i) {
            char c = s[i];
            int nxt = find_child(current, c);

            if (nxt == -1) {
                nxt = add_child(current, c);
                nodes[nxt].index = starting_index;
            }

            current = nxt;
            starting_index += (is_inverse ? -1 : 1);
        }
    }

    bool advance(int& cur, char c) const {
        if (cur == -1) return false;
        int v = find_child(cur, c);
        if (v == -1) return false;
        cur = v;
        return true;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s, t, rev_s;
    std::cin >> s >> t;
    rev_s = s;
    std::reverse(rev_s.begin(), rev_s.end());

    Trie T = Trie(), revT = Trie();
    for (int i = 0; i < (int)s.size(); ++i) {
        T.add_word(s, i, i);
        revT.add_word(rev_s, i, (int)s.size() - i - 1, true);
    }

    std::vector<int> dp(t.size() + 1, 1e9);
    std::vector<std::pair<int,int>> choice(t.size() + 1);
    dp[0] = 0;
    choice[0] = {-1, -1};

    auto step = [&](int cur, int right, const Trie& trie, bool is_inverse) {
        for (int left = right; left >= 0; --left) {
            if (!trie.advance(cur, t[left])) break;

            int add = dp[left] + 1;

            if (add < dp[right + 1]) {
                dp[right + 1] = add;
                int len = right - left + 1;

                if (is_inverse) {
                    int start = trie.nodes[cur].index + 1;
                    int end = trie.nodes[cur].index + len;
                    choice[right + 1] = {start, end};
                } else {
                    int end = trie.nodes[cur].index + 1;
                    int start = trie.nodes[cur].index - len + 2;
                    choice[right + 1] = {end, start};
                }
            }
        }
    };

    for (int right = 0; right < (int)t.size(); ++right) {
        step(T.root, right, T, false);
        step(revT.root, right, revT, true);
    }

    if (dp[t.size()] == 1e9) {
        std::cout << -1;
        return 0;
    }
    std::cout << dp[t.size()] << '\n';

    std::vector<std::pair<int,int>> res;
    int cur = t.size();

    while (cur > 0) {
        res.push_back(choice[cur]);
        cur -= std::abs(choice[cur].first - choice[cur].second) + 1;
    }

    for (int i = (int)res.size() - 1; i >= 0; --i)
        std::cout << res[i].first << ' ' << res[i].second << '\n';
}