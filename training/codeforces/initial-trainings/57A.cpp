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

void solve() {
    int n, x1, y1, x2, y2;
    cin >> n >> x1 >> y1 >> x2 >> y2;

    int side1 = 0;
    if (x1 == 0) side1 = 1;
    else if (x1 == n) side1 = 3;
    else {
        if (y1 == 0) side1 = 4;
        else side1 = 2;
    }

    int side2 = 0;
    if (x2 == 0) side2 = 1;
    else if (x2 == n) side2 = 3;
    else {
        if (y2 == 0) side2 = 4;
        else side2 = 2;
    }

    if (side1 > side2) {
        swap(side1, side2);
        swap(x1, x2);
        swap(y1, y2);
    }

    if (side1 == 1 && side2 == 3) {
        cout << n + min(y1 + y2, n - y1 + n - y2);
    } else if (side1 == 2 && side2 == 4) {
        cout << n + min(x1 + x2, n - x1 + n - x2);
    } else {
        cout << abs(x1 - x2) + abs(y1 - y2);
    }
}