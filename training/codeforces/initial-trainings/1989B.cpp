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
     cin >> T;
    while (T--) solve();
}
// clang-format on

void solve() {
    string a, b;
    cin >> a >> b;
    int n = a.size() + b.size();

    int ans = 0;
    for (int i = 0; i < b.size(); ++i) {
        int cnt = 0;

        int b_ptr = i;
        int a_ptr = 0;
        while (a_ptr < a.size() && b_ptr < b.size()) {
            while (a_ptr < a.size() && b_ptr < b.size() && a[a_ptr] != b[b_ptr]) a_ptr++;

            if (a_ptr != a.size()) {
                a_ptr++;
                b_ptr++;
                cnt++;
            }
        }

        chmax(ans, cnt);
    }

    cout << n - ans << '\n';
}