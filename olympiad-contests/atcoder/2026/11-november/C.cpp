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
    // cin >> T;
    while (T--) solve();
}
// clang-format on

void solve() {
    int n;
    cin >> n;
    vi a(n), b(n);
    get_vector(a);
    get_vector(b);


    int first = -1;
    int second = -1;

    for (int i = 0; i < n; ++i) {
        if (a[i] != b[i]) {
            first = first == -1 ? i : first;
            second = i;
        }
    }

    if (first == -1) {
        cout << "Yes";
        return;
    }

    vi a1(all(a));
    a1.erase(a1.begin() + second);
    a1.insert(a1.begin() + first, a[second]);

    vi a2(all(a));
    a2.erase(a2.begin() + first);
    a2.insert(a2.begin() + second, a[first]);

    bool good1 = true;
    bool good2 = true;
    for (int i = 0; i < n; ++i) {
        good1 &= a1[i] == b[i];
        good2 &= a2[i] == b[i];
    }

    if (good1 || good2) {
        cout << "Yes";
        return;
    }

    cout << "No";
}