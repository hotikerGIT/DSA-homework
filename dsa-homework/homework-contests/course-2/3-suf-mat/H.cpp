#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#define int long long

const int MAXLEN = 1e6;

struct state {
    int max_len = 0;
    int next[26];
    int suf_link = -1;

    state() {
        std::fill(next, next + 26, -1);
    }
};

class SufAuto {
public:
    std::vector<state> st;
    std::vector<std::map<int, int>*> mp;
    int last = 0;

    SufAuto() {
        st.reserve(2 * MAXLEN + 5);
        mp.reserve(2 * MAXLEN + 5);

        st.emplace_back();
        mp.push_back(nullptr);
        last = 0;
    }

    ~SufAuto() {
        for (auto p : mp) delete p;
    }

    void add_cnt(int v, int id, int delta) {
        if (mp[v] == nullptr) {
            mp[v] = new std::map<int, int>();
        }
        (*mp[v])[id] += delta;
    }

    int add_char(int last, int c, int id) {
        if (st[last].next[c] != -1) {
            int q = st[last].next[c];

            if (st[q].max_len == st[last].max_len + 1) {
                add_cnt(q, id, 1);
                return q;
            }

            int clone = (int)st.size();
            st.emplace_back();
            mp.push_back(nullptr);

            st[clone].max_len = st[last].max_len + 1;
            st[clone].suf_link = st[q].suf_link;
            std::copy(std::begin(st[q].next), std::end(st[q].next), std::begin(st[clone].next));

            int p = last;
            while (p != -1 && st[p].next[c] == q) {
                st[p].next[c] = clone;
                p = st[p].suf_link;
            }

            st[q].suf_link = clone;
            add_cnt(clone, id, 1);
            return clone;
        }

        int cur = (int)st.size();
        st.emplace_back();
        mp.push_back(nullptr);

        st[cur].max_len = st[last].max_len + 1;

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
                int clone = (int)st.size();
                st.emplace_back();
                mp.push_back(nullptr);

                st[clone].max_len = st[p].max_len + 1;
                st[clone].suf_link = st[q].suf_link;
                std::copy(std::begin(st[q].next), std::end(st[q].next), std::begin(st[clone].next));

                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].suf_link;
                }

                st[q].suf_link = clone;
                st[cur].suf_link = clone;
            }
        }

        add_cnt(cur, id, 1);
        return cur;
    }

    void calc() {
        int n = (int)st.size();

        int max_len = 0;
        for (const auto& s : st) {
            max_len = std::max(max_len, s.max_len);
        }

        std::vector<int> bucket(max_len + 1, 0);
        for (const auto& s : st) {
            ++bucket[s.max_len];
        }

        for (int i = 1; i <= max_len; ++i) {
            bucket[i] += bucket[i - 1];
        }

        std::vector<int> order(n);
        for (int i = n - 1; i >= 0; --i) {
            int len = st[i].max_len;
            order[--bucket[len]] = i;
        }

        for (int i = n - 1; i >= 0; --i) {
            int v = order[i];
            int link = st[v].suf_link;

            if (link > 0 && mp[v] != nullptr) {
                for (const auto& p : *mp[v]) {
                    add_cnt(link, p.first, p.second);
                }
            }
        }
    }
};

struct Query {
    int type;
    int x;
    int id;
};

signed main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int q;
    std::cin >> q;

    std::vector<Query> queries(q);
    std::vector<std::string> strings;
    std::map<std::string, int> idMap;

    auto getId = [&](const std::string& s) -> int {
        auto it = idMap.find(s);
        if (it != idMap.end()) return it->second;

        int id = (int)strings.size();
        strings.push_back(s);
        idMap[s] = id;
        return id;
    };

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1 || type == 2) {
            int x;
            std::string s;
            std::cin >> x >> s;

            int id = getId(s);
            queries[i] = {type, x, id};
        } else {
            std::string s;
            std::cin >> s;

            int id = getId(s);
            queries[i] = {3, 0, id};
        }
    }

    SufAuto sam;

    for (int id = 0; id < (int)strings.size(); ++id) {
        int last = 0;

        for (char ch : strings[id]) {
            last = sam.add_char(last, ch - 'a', id);
        }
    }

    sam.calc();

    std::vector<int> current((int)strings.size(), 0);

    for (const auto& query : queries) {
        if (query.type == 1) {
            current[query.id] += query.x;
        } else if (query.type == 2) {
            current[query.id] -= query.x;
        } else {
            int v = 0;
            bool ok = true;

            for (char ch : strings[query.id]) {
                int c = ch - 'a';

                if (sam.st[v].next[c] == -1) {
                    ok = false;
                    break;
                }

                v = sam.st[v].next[c];
            }

            int ans = 0;

            if (ok && sam.mp[v] != nullptr) {
                for (const auto& p : *sam.mp[v]) {
                    ans += p.second * current[p.first];
                }
            }

            std::cout << ans << '\n';
        }
    }
}