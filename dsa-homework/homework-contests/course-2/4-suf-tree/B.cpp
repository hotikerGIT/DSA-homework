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
    std::vector<int> occ;
    State ptr{0, 0};
    int n;

    explicit SuffixTree(std::string str) : s(std::move(str)) {
        s.push_back('\0');
        n = s.size();

        t.reserve(2 * n);
        t.emplace_back(0, 0, -1);
        t[0].link = 0;

        for (int i = 0; i < n; ++i) extend(i);

        occ.resize(t.size());
        auto dfs_leaf_cnt = [&](int cur, auto&& self) -> int {
            auto& cur_state = t[cur];
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

    State go(State st, char c) const {
        if (st.pos == t[st.v].len()) {
            int to = t[st.v].get(c);

            if (to == -1) return {-1, -1};
            st = {to, 1};

        } else {
            if (s[t[st.v].l + st.pos] != c)
                return {-1, -1};

            st.pos++;
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
    std::string s1, s2;
    std::cin >> s1 >> s2;

    auto T1 = SuffixTree(s1);
    auto T2 = SuffixTree(s2);

    int ans = 1e9;
    for (int i = 0; i < s1.size(); ++i) {
        auto state1 = SuffixTree::State(0, 0);
        auto state2 = SuffixTree::State(0, 0);

        for (int j = 0; i + j < s1.size(); ++j) {
            state1 = T1.go(state1, s1[i + j]);
            state2 = T2.go(state2, s1[i + j]);

            if (state1.v == -1 || state2.v == -1) break;

            if (T1.occ[state1.v] == 1 && T2.occ[state2.v] == 1) ans = std::min(ans, j + 1);
        }
    }

    std::cout << (ans == 1e9 ? -1 : ans);
}