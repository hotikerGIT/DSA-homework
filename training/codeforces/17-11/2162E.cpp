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
using ordered_multiset = tree<T, null_type, std::less<T>,
        rb_tree_tag, tree_order_statistics_node_update>;

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

template <class T>
void get_vector(vector<T>& a) {
    for (int i = 0; i < a.size(); ++i) std::cin >> a[i];
}

template <class T>
vector<T> read_vector(int size) {
    vector<T> res(size);
    for (int i = 0; i < res.size(); ++i) std::cin >> res[i];
    return res;
}

constexpr int INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 362880;

static void solve();

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
     cin >> T;
    while (T--) solve();
}
// clang-format on

void solve() {
    int n, k;
    cin >> n >> k;
    vi a(n);
    get_vector(a);

    vi res;
    vi cnt(n + 1);
    for (int num : a) cnt[num]++;
    for (int i = 1; i <= n && res.size() < k; ++i) if (cnt[i] == 0) res.push_back(i);

    map<int, int> right;
    for (int i = 0; i < n; ++i) right[a[i]] = i;
    vector<pii> sorted_right;
    for (auto& [num, pos] : right) sorted_right.emplace_back(pos, num);
    sort(all(sorted_right));

    for (int i = 0; res.size() < k; ++i) {
        res.push_back(sorted_right[i].second);
    }

    for (int num : res) cout << num << ' ';
    cout << nn;
}