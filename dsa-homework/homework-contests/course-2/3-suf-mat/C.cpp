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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    string s;
    cin >> n >> s;

    SufAuto SM(s);

    vector<int> spf(n + 1, 0);
    for (int i = 2; i <= n; ++i) {
        if (spf[i] == 0) {
            spf[i] = i;
            if ((ll)i * i <= n) {
                for (int j = i * i; j <= n; j += i) {
                    if (spf[j] == 0) spf[j] = i;
                }
            }
        }
    }

    ll res = 0;
    vector<int> divs;
    divs.reserve(256);

    for (const auto& state : SM.st) {
        int occ = state.occ;
        if (occ == 0) continue;

        int link_len = (state.suf_link != -1)
                       ? SM.st[state.suf_link].max_len
                       : 0;

        if (occ == 1) {
            if (link_len < 1 && 1 <= state.max_len) {
                res += 1;
            }
            continue;
        }

        divs.clear();
        divs.push_back(1);

        int x = occ;
        while (x > 1) {
            int p = spf[x];
            int exp = 0;
            while (x % p == 0) {
                x /= p;
                ++exp;
            }

            int sz = (int)divs.size();
            int cur_mult = 1;
            for (int e = 1; e <= exp; ++e) {
                cur_mult *= p;
                for (int i = 0; i < sz; ++i) {
                    divs.push_back(divs[i] * cur_mult);
                }
            }
        }

        for (int d : divs) {
            if (link_len < d && d <= state.max_len) {
                res += occ;
            }
        }
    }

    cout << res << '\n';
    return 0;
}