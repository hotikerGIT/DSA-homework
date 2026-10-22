#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

#define int long long
using ll = long long;

struct state {
    int max_len = 0;
    int next[26];
    int suf_link = -1;
    int occ = 0;
    int cost = 0;

    state() {
        std::fill(next, next + 26, -1);
    }
};

class SufAuto {
public:
    vector<state> st;
    int last = 0;

    SufAuto() {
        st.reserve(2);
        st.emplace_back();
        last = 0;
    }

    void AddLetter(char ch, int cost) {
        int c = ch - 'a';

        if (st[last].next[c] != -1) {
            int q = st[last].next[c];
            if (st[q].max_len == st[last].max_len + 1) {
                st[q].occ += 1;
                st[q].cost += cost;
                last = q;
                return;
            }

            st.emplace_back();
            int clone = (int)st.size() - 1;
            st[clone].max_len = st[last].max_len + 1;
            st[clone].suf_link = st[q].suf_link;
            st[clone].occ = 1;
            st[clone].cost = cost;
            std::copy(std::begin(st[q].next), std::end(st[q].next),
                      std::begin(st[clone].next));

            int p = last;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].suf_link;
            }
            st[q].suf_link = clone;
            last = clone;
            return;
        }

        st.emplace_back();
        int cur = (int)st.size() - 1;
        st[cur].max_len = st[last].max_len + 1;
        st[cur].occ = 1;
        st[cur].cost = cost;

        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].suf_link;
        }

        if (p == -1) {
            st[cur].suf_link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].max_len + 1 == st[q].max_len) {
                st[cur].suf_link = q;
            } else {
                st.emplace_back();
                int clone = (int)st.size() - 1;

                st[clone].max_len = st[p].max_len + 1;
                st[clone].suf_link = st[q].suf_link;
                st[clone].occ = 0;
                st[clone].cost = 0;
                std::copy(std::begin(st[q].next), std::end(st[q].next),
                          std::begin(st[clone].next));

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].suf_link;
                }

                st[q].suf_link = clone;
                st[cur].suf_link = clone;
            }
        }

        last = cur;
    }

    void add_string(const string& s, int cost) {
        last = 0;
        for (char ch : s) {
            AddLetter(ch, cost);
        }
    }

    void calc() {
        int n = (int)st.size();
        int max_len = 0;
        for (const auto& s : st) {
            if (s.max_len > max_len) max_len = s.max_len;
        }

        vector<int> cnt(max_len + 1, 0);
        for (const auto& s : st) {
            ++cnt[s.max_len];
        }

        for (int i = 1; i <= max_len; ++i) {
            cnt[i] += cnt[i - 1];
        }

        vector<int> order(n);
        for (int i = n - 1; i >= 0; --i) {
            int len = st[i].max_len;
            order[--cnt[len]] = i;
        }

        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            int suf_link = st[v].suf_link;
            if (suf_link != -1) {
                st[suf_link].occ += st[v].occ;
                st[suf_link].cost += st[v].cost;
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    std::vector<std::string> strings(n);
    std::vector<int> costs(n);

    SufAuto SM;
    for (int i = 0; i < n; ++i) std::cin >> strings[i];
    for (int i = 0; i < n; ++i) std::cin >> costs[i];

    for (int i = 0; i < n; ++i) {
        SM.add_string(strings[i], costs[i]);
    }
    SM.calc();

    int res = 0;
    for (auto& state : SM.st) {
        res = std::max(res, state.cost * state.max_len);
    }

    std::cout << res;
}