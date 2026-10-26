#include <iostream>
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <string>
#include <functional>

#define ll long long
#define int long long

using namespace std;

const ll MAXLEN = 5005;

struct state {
    ll right_index = -1;
    ll max_len = 0;
    map<char, ll> next;
    ll suf_link = -1;
    ll occ = 0;
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
        st[cur].occ = 1;
        st[cur].right_index = st[last].right_index+1;

        ll p = last;
        do {
            for (; p > -1 && st[p].next.count(ch) == 0; p = st[p].suf_link) {
                st[p].next[ch] = cur;
            }
            if (p == -1) {
                st[cur].suf_link = 0;
                break;
            }

            ll q = st[p].next[ch];
            if (st[p].max_len+1 == st[q].max_len){
                st[cur].suf_link = q;
                break;
            }

            st.emplace_back();
            ll qv = st.size()-1;

            st[qv].next = st[q].next;

            st[qv].suf_link = st[q].suf_link;
            st[q].suf_link = qv;
            st[cur].suf_link = qv;

            st[qv].max_len = st[p].max_len+1;
            st[qv].right_index = st[q].right_index;

            for (; p > -1 && st[p].next[ch] == q; p = st[p].suf_link) {
                st[p].next[ch] = qv;
            }

        } while(false);

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
                st[st[v].suf_link].occ += st[v].occ;
            }
        }
    }

    bool has_unique_word(const std::string& word) {
        int cur = 0;

        for (char c : word) {
            if (!st[cur].next.contains(c)) return false;
            cur = st[cur].next[c];
        }

        return st[cur].occ == 1;
    }

    int max_prefix(const std::string& word) {
        int cur = 0;
        int res = 0;

        for (char c : word) {
            if (!st[cur].next.contains(c)) return res;
            cur = st[cur].next[c];
            ++res;
        }

        return res;
    }
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string s1, s2;
    std::cin >> s1 >> s2;

    auto SM1 = SufAuto(s1);
    auto SM2 = SufAuto(s2);
    int res = 1e9;

    std::function<void(int, int)> dfs = [&](int cur1, int cur2) {
        auto& state1 = SM1.st[cur1];
        auto& state2 = SM2.st[cur2];
        state1.occ2 = state2.occ;

        int link_len1 = state1.suf_link != -1 ? SM1.st[state1.suf_link].max_len + 1 : 1e9;
        int link_len2 = state2.suf_link != -1 ? SM2.st[state2.suf_link].max_len + 1 : 1e9;
        if (state1.occ == 1 && state1.occ2 == 1) res = std::min(res, std::max(link_len1, link_len2));

        for (auto& [ch, nxt] : state1.next) {
            if (state2.next.contains(ch)) {
                dfs(nxt, state2.next[ch]);
            }
        }
    };

    dfs(0, 0);

    std::cout << (res < 1e9 ? res : -1);
}