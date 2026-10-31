#include <string>
#include <iostream>
#include <map>
#include <vector>
#define int long long

struct SuffixTree {
    struct Node {
        int l, r, par, link = -1;
        std::map<char, int> next;

        Node(int l, int r, int par) : l(l), r(r), par(par) {}

        int len() const { return r - l; }

        int get(char c) const {
            auto it = next.find(c);
            return it == next.end() ? -1 : it->second;
        }
    };

    struct State {
        int v, pos;
    };

    std::string s;
    std::vector<Node> t;
    State ptr{0, 0};
    int n;

    explicit SuffixTree(std::string str) : s(std::move(str)) {
        s.push_back('\0');
        n = s.size();

        t.reserve(2 * n);
        t.emplace_back(0, 0, -1);
        t[0].link = 0;

        for (int i = 0; i < n; ++i) extend(i);
    }

    State go(State st, int l, int r) const {
        while (l < r) {
            if (st.pos == t[st.v].len()) {
                int to = t[st.v].get(s[l]);
                if (to == -1) return {-1, -1};
                st = {to, 0};
            } else {
                if (s[t[st.v].l + st.pos] != s[l])
                    return {-1, -1};

                int take = std::min(r - l, t[st.v].len() - st.pos);
                st.pos += take;
                l += take;
            }
        }
        return st;
    }

    int split(State st) {
        if (st.pos == t[st.v].len()) return st.v;
        if (st.pos == 0) return t[st.v].par;

        int v = st.v;
        int l = t[v].l, par = t[v].par;
        int mid = t.size();

        t.emplace_back(l, l + st.pos, par);
        t[par].next[s[l]] = mid;
        t[mid].next[s[l + st.pos]] = v;

        t[v].l += st.pos;
        t[v].par = mid;

        return mid;
    }

    int get_link(int v) {
        if (t[v].link != -1) return t[v].link;

        int par = t[v].par;
        int to = get_link(par);

        State st = go(
                {to, t[to].len()},
                t[v].l + (par == 0),
                t[v].r
        );

        return t[v].link = split(st);
    }

    void extend(int pos) {
        while (true) {
            State nptr = go(ptr, pos, pos + 1);

            if (nptr.v != -1) {
                ptr = nptr;
                return;
            }

            int mid = split(ptr);
            int leaf = t.size();

            t.emplace_back(pos, n, mid);
            t[mid].next[s[pos]] = leaf;

            int to = get_link(mid);
            ptr = {to, t[to].len()};

            if (mid == 0) return;
        }
    }
};

signed main() {
    std::string s;
    int k;
    std::cin >> s >> k;

    int total = s.size() * (s.size() + 1) / 2;
    if (total < k) {
        std::cout << "No such line.";
        return 0;
    }

    auto tree = SuffixTree(s);
    int n = tree.n;

    auto valid_len = [&](int v) -> int {
        if (v == 0) return 0;
        int L = tree.t[v].len();
        if (tree.t[v].next.empty() && tree.t[v].r == n && L > 0 && tree.s[tree.t[v].r - 1] == '\0')
            return L - 1;
        return L;
    };

    std::vector<int> occ(tree.t.size());
    std::vector<int> substr_cnt(tree.t.size());

    auto dfs_leaf_cnt = [&](int cur, auto&& self) -> int {
        auto& cur_state = tree.t[cur];
        if (cur_state.next.empty()) {
            occ[cur] = 1;
            return 1;
        }

        int ans = 0;
        for (auto& [ch, nxt] : cur_state.next) {
            ans += self(nxt, self);
        }

        occ[cur] = ans;
        return ans;
    };
    dfs_leaf_cnt(0, dfs_leaf_cnt);

    auto dfs_substr_cnt = [&](int cur, auto&& self) -> int {
        auto& cur_state = tree.t[cur];

        int ans = valid_len(cur) * occ[cur];
        for (auto& [ch, nxt] : cur_state.next) {
            ans += self(nxt, self);
        }

        substr_cnt[cur] = ans;
        return ans;
    };
    dfs_substr_cnt(0, dfs_substr_cnt);

    std::string res;

    auto select = [&](int cur, auto&& self) -> bool {
        auto& cur_state = tree.t[cur];

        for (auto& [ch, nxt] : cur_state.next) {
            if (k > substr_cnt[nxt]) {
                k -= substr_cnt[nxt];
                continue;
            }

            int L = tree.t[nxt].len();
            int vl = valid_len(nxt);
            int edge_cnt = vl * occ[nxt];

            if (k <= edge_cnt) {
                int len = static_cast<int>((k - 1) / occ[nxt] + 1);
                res += tree.s.substr(tree.t[nxt].l, len);
                return true;
            }

            k -= edge_cnt;
            res += tree.s.substr(tree.t[nxt].l, L);
            return self(nxt, self);
        }

        return false;
    };

    select(0, select);

    std::cout << res;
}