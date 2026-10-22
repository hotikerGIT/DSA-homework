#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

#define int long long
using ll = long long;

const int MAXLEN = 2e5;

struct state {
    int max_len = 0;
    int next[26];
    int suf_link = -1;
    int occ = 0;

    state() {
        std::fill(next, next + 26, -1);
    }
};

class SufAuto {
public:
    vector<state> st;
    int last = 0;

    SufAuto() {
        st.reserve(2 * MAXLEN + 1);
        st.emplace_back();
        last = 0;
    }

    SufAuto(const string& s, const std::vector<int>& bad) : SufAuto() {
        for (int i = 0; i < s.size(); ++i) AddLetter(s[i], !bad[i]);
        calc();
    }

    void AddLetter(char ch, bool is_good = false) {
        int c = ch - 'a';

        st.emplace_back();
        int cur = (int)st.size() - 1;
        st[cur].max_len = st[last].max_len + 1;
        st[cur].occ = is_good;

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
            if (st[v].suf_link != -1) {
                st[st[v].suf_link].occ += st[v].occ;
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s1, s2;
    cin >> n >> s1 >> s2;
    std::vector<int> bad(n);
    for (int i = 0; i < s2.size(); ++i) bad[i] = s2[i] == '1';

    SufAuto SM(s1, bad);

    int res = 0;
    for (auto& state: SM.st) {
        res = std::max(res, state.occ * state.max_len);
    }
    std::cout << res;
}