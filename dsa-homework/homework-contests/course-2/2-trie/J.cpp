#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

std::vector<int> bijection;

struct Edge {
    int to;
    int next;
    char ch;

    Edge(int to_, int next_, char ch_) : to(to_), next(next_), ch(ch_) {}
};

struct Node {
    int head;
    std::vector<int> indexes;
    std::vector<int> free;

    Node() : head(-1) {}
};

class Trie {
public:
    std::vector<Node> nodes;
    std::vector<Edge> edges;
    std::vector<int> edgeCnt;

    Trie() {
        nodes.emplace_back();
        edgeCnt.push_back(0);
    }

    int new_node() {
        nodes.emplace_back();
        edgeCnt.push_back(0);
        return (int)nodes.size() - 1;
    }

    int find_edge(int cur, char c) const {
        for (int e = nodes[cur].head; e != -1; e = edges[e].next) {
            if (edges[e].ch == c)
                return edges[e].to;
        }
        return -1;
    }

    void add_edge(int cur, char c, int to) {
        int e = (int)edges.size();
        edges.emplace_back(to, -1, c);

        int* p = &nodes[cur].head;
        while (*p != -1 && edges[*p].ch < c) {
            p = &edges[*p].next;
        }

        edges[e].next = *p;
        *p = e;
    }

    void add_word(const std::string& word, int index) {
        int cur = 0;
        for (char c : word) {
            int nxt = find_edge(cur, c);
            if (nxt == -1) {
                nxt = new_node();
                add_edge(cur, c, nxt);
            }
            edgeCnt[nxt]++;
            cur = nxt;
        }
        nodes[cur].free.push_back(index);
    }

    int clear_word(const std::string& word, int index) {
        int cur = 0;
        int res = 0;
        for (char c : word) {
            int nxt = find_edge(cur, c);
            if (nxt == -1) {
                nodes[cur].indexes.push_back(index);
                return res;
            }

            if (edgeCnt[nxt] > 0) {
                edgeCnt[nxt]--;
                res++;
            }
            cur = nxt;
        }

        nodes[cur].indexes.push_back(index);
        return res;
    }
};

void dfs(std::vector<Node>& nodes, const std::vector<Edge>& edges, int cur) {
    if (cur == -1) return;

    for (int e = nodes[cur].head; e != -1; e = edges[e].next) {
        int nxt = edges[e].to;
        dfs(nodes, edges, nxt);

        if (nodes[cur].free.size() < nodes[nxt].free.size())
            std::swap(nodes[nxt].free, nodes[cur].free);
        for (int num : nodes[nxt].free) nodes[cur].free.push_back(num);
        nodes[nxt].free.clear();

        if (nodes[cur].indexes.size() < nodes[nxt].indexes.size())
            std::swap(nodes[nxt].indexes, nodes[cur].indexes);
        for (int num : nodes[nxt].indexes) nodes[cur].indexes.push_back(num);
        nodes[nxt].indexes.clear();
    }

    int k = std::min(nodes[cur].free.size(), nodes[cur].indexes.size());
    for (int i = 0; i < k; ++i) {
        bijection[nodes[cur].free.back()] = nodes[cur].indexes.back();
        nodes[cur].free.pop_back();
        nodes[cur].indexes.pop_back();
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    Trie T;
    bijection.assign(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        T.add_word(s, i + 1);
    }

    int res = 0;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        res += T.clear_word(s, i + 1);
    }

    dfs(T.nodes, T.edges, 0);

    auto& free = T.nodes[0].free;
    for (int i = 1; i <= n; ++i) {
        if (bijection[i] == 0) {
            bijection[i] = free.back();
            free.pop_back();
        }
    }

    std::cout << res << '\n';
    for (int i = 1; i <= n; ++i) {
        std::cout << i << ' ' << bijection[i] << '\n';
    }
}