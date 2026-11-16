// clang-format off
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

#define int long long

using vi = vector<int>; using vvi = vector<vi>;
using pii = pair<int, int>; using vpii = vector<pii>;

using H = decltype([](uint64_t x) {
    static const uint64_t r = chrono::steady_clock::now().time_since_epoch().count();
    x += r + 0x9e3779b97f4a7c15ULL; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL; return x ^ (x >> 31);
});

template<class K, class V> using hash_map = __gnu_pbds::gp_hash_table<K, V, H>;
template<class K> using hash_set = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, H>;

#define all(x) begin(x), end(x)
#define rall(x) rbegin(x), rend(x)
#define nn '\n'

template <class T>
static int sz(const T& x) { return (int)size(x); }

template <class T, class U>
static bool chmin(T& a, const U& b) { return b < a ? (a = b, true) : false; }

template <class T, class U>
static bool chmax(T& a, const U& b) { return a < b ? (a = b, true) : false; }

void get_vector(vector<int>& a, int n) {
    for (int i = 0; i < n; ++i) std::cin >> a[i];
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

struct DSU {
    vi parent, size;

    DSU(int n) {
        size.resize(n, 1);
        parent.resize(n);
        std::iota(all(parent), 0);
    }

    int find(int x) {
        if (x == parent[x]) return x;
        return parent[x] = find(parent[x]);
    }

    bool connected(int x, int y) { return find(x) == find(y); }

    bool unite(int x, int y) {
        x = find(x);
        y = find(y);

        if (x == y) return false;

        if (size[x] < size[y]) std::swap(x, y);

        size[x] += size[y];
        parent[y] = x;

        return true;
    }
};

void solve() {
    int n;
    cin >> n;
    vi a(n);
    get_vector(a, n);

    auto dsu = DSU(n);

    for (int i = 0; i < n; ++i) {
        dsu.unite(i, a[i] - 1);
    }

    std::set<int> cnt;
    for (int i = 0; i < n; ++i) cnt.insert(dsu.find(i));

    std::cout << cnt.size();
}