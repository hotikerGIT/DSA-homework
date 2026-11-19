// clang-format off
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;

#define int long long

using vi = vector<int>; using vvi = vector<vi>;
using pii = pair<int, int>; using vpii = vector<pii>;

template<class T>
using ordered_set = tree<T, null_type, std::less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define nn '\n'

template <class T, class U>
static bool chmin(T& a, const U& b) { return b < a ? (a = b, true) : false; }

template <class T, class U>
static bool chmax(T& a, const U& b) { return a < b ? (a = b, true) : false; }

template <typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v) {
    for (auto& x : v) {
        is >> x;
    }
    return is;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v) {
    for (std::size_t i = 0; i < v.size(); ++i) {
        if (i) os << ' ';
        os << v[i];
    }
    return os;
}

constexpr int INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 362880;

static void solve();

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) solve();
}
// clang-format on

class DSU {
public:
    DSU(int n) : p(n), s(n, 1) {
        std::iota(p.begin(), p.end(), 0);
    }

    bool share(int u, int v) {return root(u) == root(v);}

    void unite(int u, int v) {
        int ru = root(u), rv = root(v);
        if (ru == rv) {return;}
        if (s[ru] > s[rv]) {
            std::swap(u, v);
            std::swap(ru, rv);
        }
        p[ru] = rv; s[rv] += s[ru];
    }

    std::vector<int> p, s;

    int root(int x) {
        if (p[x] == x) {return x;}
        int r = root(p[x]);
        return p[x] = r;
    }
};


void solve() {
    int n;
    cin >> n;
    vi p(n);
    cin >> p;

    DSU dsu(n + 1);
    for (int pos = 0; pos < n; ++pos) {
        dsu.unite(pos + 1, p[pos]);
    }

    multiset<int> sizes;
    vi visited(n + 1);
    for (int i = 1; i <= n; ++i) {
        if (visited[dsu.root(i)]) continue;
        visited[dsu.root(i)] = 1;
        sizes.insert(dsu.s[dsu.root(i)]);
    }

    if (sizes.size() == 1) {
        int sz = *sizes.begin();
        cout << sz * sz;
        return;
    }

    int first = *sizes.rbegin();
    sizes.erase(prev(sizes.end()));
    int second = *sizes.rbegin();
    sizes.erase(prev(sizes.end()));
    int ans = (first + second) * (first + second);

    for (int num : sizes) {
        ans += num * num;
    }

    cout << ans;
}