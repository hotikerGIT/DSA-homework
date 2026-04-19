#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
struct Node{
    bool f = false;
    int last_seen = 0;
    vector<int> v;
};

vector<Node> segtree;

void merge(int v) {
    auto& v1 = segtree[2*v+1].v;
    auto& v2 = segtree[2*v+2].v;
    int a = v1.size(), b = v2.size(), i = 0, j = 0;
    while (i < a && j < b) {
        if (v1[i] <= v2[j]) {
            segtree[v].v.push_back(v1[i++]);
        } else {
            segtree[v].v.push_back(v2[j++]);
        }
    }
    while (i < a) {
        segtree[v].v.push_back(v1[i++]);
    }
    while (j < b) {
        segtree[v].v.push_back(v2[j++]);
    }
}

void build(vector<int>& a, int v, int l, int r) {
    if (l == r) {
        segtree[v].v.push_back(a[l]);
        return;
    }
    int m = (l + r) / 2;
    build(a, 2*v+1, l, m);
    build(a, 2*v+2, m+1, r);
    merge(v);
}

void push(int v, int l, int r) {
    if (!segtree[v].f) {
        return;
    }
    if (l != r) {
        segtree[2*v+1].last_seen = segtree[v].last_seen;
        segtree[2*v+2].last_seen = segtree[v].last_seen;
        segtree[2*v+1].f = true;
        segtree[2*v+2].f = true;
    }
    segtree[v].f = false;
}

int update(int v, int tl, int tr, int l, int r, int x) {
    push(v, l, r);
    if (tr < l || r < tl) {
        return 0;
    }
    if (tl <= l && r <= tr) {
        segtree[v].f = true;
        auto& vec = segtree[v].v;
        auto beg = lower_bound(vec.begin(), vec.end(), segtree[v].last_seen);
        auto end = lower_bound(vec.begin(), vec.end(), x);
        segtree[v].last_seen = x;
        return distance(beg, end);
    }
    int m = (l + r) / 2;
    return update(2*v+1, tl, tr, l, m, x) + update(2*v+2, tl, tr, m+1, r, x);
}

void solve() {
    int n, ans = 0;
    cin >> n;
    vector<int> a(n);
    map<int, pair<int, int>> m;
    for (int i=0; i<n; ++i) {
        cin >> a[i];
        if (m.find(a[i]) == m.end()) {
            m[a[i]].first = i;
            m[a[i]].second = i;
        } else {
            m[a[i]].second = i;
        }
    }
    segtree.assign(4*n, Node{});
    build(a, 0, 0, n-1);
    for (auto x: m) {
        auto [b, e] = x.second;
        ans += update(0, b, e, 0, n-1, x.first);
    }
    cout << ans << endl;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}