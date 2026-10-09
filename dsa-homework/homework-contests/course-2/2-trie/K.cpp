#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <algorithm>

constexpr int ALPHABET = 26;

struct Node {
    bool is_terminal = false;

    int pref_size = 0;
    int suf_link = 0;
    int comp_link = -1;
    int parent = 0;
    int ch = 0;

    int go_to[ALPHABET];

    Node() {
        std::fill(go_to, go_to + ALPHABET, 0);
    }
};

struct Aho {
    std::vector<Node> nodes;
    std::deque<int> terminals;
    std::set<std::string> contained;
    std::vector<int> visited, cnt;
    int query_id = 0;

    Aho() {
        nodes.emplace_back();
    }

    void add_word(const std::string& word) {
        contained.insert(word);

        int cur = 0;

        for (char c : word) {
            int ind = c - 'a';

            if (!nodes[cur].go_to[ind]) {
                nodes[cur].go_to[ind] = nodes.size();
                nodes.emplace_back();

                int nxt = nodes[cur].go_to[ind];
                nodes[nxt].parent = cur;
                nodes[nxt].ch = ind;
                nodes[nxt].pref_size = nodes[cur].pref_size + 1;
            }

            cur = nodes[cur].go_to[ind];
        }

        nodes[cur].is_terminal = true;
    }

    bool delete_word(const std::string& word) {
        int cur = 0;

        for (char c : word) {
            int ind = c - 'a';
            int nxt = nodes[cur].go_to[ind];

            if (nodes[cur].pref_size + 1 != nodes[nxt].pref_size) return false;
            cur = nxt;
        }

        if (!nodes[cur].is_terminal) return false;
        nodes[cur].is_terminal = false;
        contained.erase(word);
        return true;
    }

    void build() {
        std::queue<int> queue;
        queue.push(0);

        while (!queue.empty()) {
            int cur = queue.front();
            Node& cur_node = nodes[cur];
            queue.pop();

            for (int nxt : cur_node.go_to) {
                if (nxt) queue.push(nxt);
            }

            if (cur == 0) continue;

            if (cur_node.is_terminal) terminals.push_front(cur);

            if (cur_node.parent == 0) {
                cur_node.suf_link = 0;
            } else {
                cur_node.suf_link = nodes[nodes[cur_node.parent].suf_link].go_to[cur_node.ch];
            }

            if (nodes[cur_node.suf_link].is_terminal) {
                cur_node.comp_link = cur_node.suf_link;
            } else {
                cur_node.comp_link = nodes[cur_node.suf_link].comp_link;
            }

            for (int i = 0; i < ALPHABET; ++i) {
                if (cur_node.go_to[i]) continue;

                cur_node.go_to[i] = nodes[cur_node.suf_link].go_to[i];
            }
        }

        visited.resize(nodes.size(), 0);
        cnt.resize(nodes.size(), 0);
    }

    int solve(const std::string& word) {
        ++query_id;
        std::vector<int> query_nodes;
        query_nodes.reserve(word.size() * 2);

        auto touch = [&](int v) {
            if (visited[v] != query_id) {
                visited[v] = query_id;
                cnt[v] = 0;
                query_nodes.push_back(v);
            }
        };

        int cur = 0;
        for (char c : word) {
            cur = nodes[cur].go_to[c - 'a'];
            touch(cur);
            cnt[cur]++;
        }

        for (size_t i = 0; i < query_nodes.size(); ++i) {
            int id = query_nodes[i];
            while (nodes[id].comp_link != -1) {
                int nxt = nodes[id].comp_link;
                if (visited[nxt] == query_id) break;
                touch(nxt);
                id = nxt;
            }
        }

        std::sort(query_nodes.begin(), query_nodes.end(),
                  [&](int a, int b) { return nodes[a].pref_size > nodes[b].pref_size; });

        int res = 0;
        for (int term : query_nodes) {
            if (nodes[term].is_terminal) res += cnt[term];
            if (nodes[term].comp_link != -1)
                cnt[nodes[term].comp_link] += cnt[term];
        }
        return res;
    }
};

struct Decompose {
    std::vector<Aho> decompose;

    Decompose() {
        decompose.resize(32, Aho());
    }

    void add_word(const std::string& word) {
        Aho carry;
        carry.add_word(word);
        carry.build();

        for (int i = 0; i < 32; ++i) {
            if (decompose[i].contained.empty()) {
                decompose[i] = std::move(carry);
                return;
            }

            Aho merged;
            for (auto& s : decompose[i].contained) merged.add_word(s);
            for (auto& s : carry.contained) merged.add_word(s);
            merged.build();

            carry = std::move(merged);
            decompose[i] = Aho();
        }
    }

    void delete_word(const std::string& word) {
        for (auto& aho : decompose) {
            if (aho.delete_word(word)) break;
        }
    }

    void solve(const std::string& word) {
        int res = 0;

        for (auto& aho : decompose) {
            if (aho.contained.empty()) continue;
            res += aho.solve(word);
        }

        std::cout << res << std::endl;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int m;
    std::cin >> m;

    Decompose D;

    for (int i = 0; i < m; ++i) {
        int type;
        std::string word;
        std::cin >> type >> word;

        if (type == 1) D.add_word(word);
        if (type == 2) D.delete_word(word);
        if (type == 3) D.solve(word);
    }
}