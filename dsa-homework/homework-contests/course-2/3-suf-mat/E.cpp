#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <numeric>

using namespace std;

using ll = long long;

const int MAXLEN = 1e6;

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

    SufAuto(const string& s) : SufAuto() {
        for (char ch : s) AddLetter(ch);
        calc();
    }

    void AddLetter(char ch) {
        int c = ch - 'a';

        st.emplace_back();
        int cur = (int)st.size() - 1;
        st[cur].max_len = st[last].max_len + 1;
        st[cur].occ = 1;

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
        for (const auto& s : st)
            if (s.max_len > max_len) max_len = s.max_len;

        vector<int> cnt(max_len + 1, 0);
        for (const auto& s : st) ++cnt[s.max_len];
        for (int i = 1; i <= max_len; ++i) cnt[i] += cnt[i - 1];

        vector<int> order(n);
        for (int i = n - 1; i >= 0; --i) {
            int len = st[i].max_len;
            order[--cnt[len]] = i;
        }

        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            if (st[v].suf_link != -1)
                st[st[v].suf_link].occ += st[v].occ;
        }
    }

    void solve(std::string& x) {
        int n = (int)x.size();

        vector<int> pi(n, 0);
        for (int i = 1; i < n; ++i) {
            int j = pi[i - 1];
            while (j > 0 && x[i] != x[j]) j = pi[j - 1];
            if (x[i] == x[j]) ++j;
            pi[i] = j;
        }
        int p0 = n - pi[n - 1];
        int p  = (n % p0 == 0) ? p0 : n;

        x += x;

        int v = 0;
        int l = 0;
        ll res = 0;

        for (int i = 0; i < n + p - 1; ++i) {
            int c = x[i] - 'a';

            while (v != 0 && st[v].next[c] == -1) {
                v = st[v].suf_link;
                l = st[v].max_len;
            }
            if (st[v].next[c] != -1) {
                v = st[v].next[c];
                ++l;
            } else {
                v = 0;
                l = 0;
            }

            if (i < n - 1) continue;
            if (l < n)     continue;

            int u = v;
            while (st[u].suf_link != -1 && st[st[u].suf_link].max_len >= n)
                u = st[u].suf_link;

            res += st[u].occ;
        }

        std::cout << res << '\n';
    }
};

int main() {
    std::string s;
    std::cin >> s;

    auto SM = SufAuto(s);

    int n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::string t;
        std::cin >> t;
        SM.solve(t);
    }
}