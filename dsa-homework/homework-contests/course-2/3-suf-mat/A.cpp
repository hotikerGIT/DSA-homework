#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <string>

#define ll long long
#define int long long

using namespace std;

const ll MAXLEN = 100000;

struct state {
    ll max_len = 0;
    map<char, ll> next;
    ll suf_link = -1;
    ll occ1 = 0;
    ll dp = 0;
};

class SufAuto {
public:
    vector<state> st;
    ll last = 0;

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
        st.emplace_back();
        ll cur = st.size() - 1;
        st[cur].max_len = st[last].max_len + 1;
        st[cur].occ1 = 1;

        ll p = last;
        while (p != -1 && st[p].next.count(ch) == 0) {
            st[p].next[ch] = cur;
            p = st[p].suf_link;
        }

        if (p == -1) {
            st[cur].suf_link = 0;
        } else {
            ll q = st[p].next[ch];
            if (st[p].max_len + 1 == st[q].max_len) {
                st[cur].suf_link = q;
            } else {
                st.emplace_back();
                ll clone = st.size() - 1;
                st[clone].next = st[q].next;
                st[clone].suf_link = st[q].suf_link;
                st[clone].max_len = st[p].max_len + 1;
                st[clone].occ1 = 0;

                while (p != -1 && st[p].next[ch] == q) {
                    st[p].next[ch] = clone;
                    p = st[p].suf_link;
                }

                st[q].suf_link = clone;
                st[cur].suf_link = clone;
            }
        }

        last = cur;
    }

    void calc() {
        int n = st.size();
        vector<int> order(n);
        iota(order.begin(), order.end(), 0);

        sort(order.begin(), order.end(), [&](int a, int b) {
            return st[a].max_len > st[b].max_len;
        });

        for (int v : order) {
            if (st[v].suf_link != -1) {
                st[st[v].suf_link].occ1 += st[v].occ1;
            }
        }

        for (int v : order) {
            st[v].dp = st[v].occ1;
            for (auto& [ch, to] : st[v].next) {
                st[v].dp += st[to].dp;
            }
        }
    }
};

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    int k;
    cin >> s >> k;

    int n = s.size();
    int total = n * (n + 1) / 2;

    if (k > total) {
        cout << "No such line.";
        return 0;
    }

    SufAuto SM(s);

    string res;
    int cur = 0;

    while (true) {
        for (auto& [ch, to] : SM.st[cur].next) {
            int cnt = SM.st[to].dp;

            if (k <= cnt) {
                res += ch;

                if (k <= SM.st[to].occ1) {
                    cout << res;
                    return 0;
                }

                k -= SM.st[to].occ1;
                cur = to;
                break;
            } else {
                k -= cnt;
            }
        }
    }
}