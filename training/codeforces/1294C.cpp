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
    int n;
    cin >> n;
    int x = n;

    map<int, int> factors;
    for (int i = 2; i * i <= n; ++i) {
        while (x % i == 0) {
            factors[i]++;
            x /= i;
        }
    }

    if (x != 1) factors[x]++;

    int a = 0;
    int b = 0;
    int c = 0;

    if (factors.size() == 1) {
        auto it = factors.begin();
        if (it->second < 6) {
            std::cout << "NO\n";
            return;
        }

        a = it->first;
        b = a * a;
        c = n / (a * b);
    }

    if (factors.size() == 2) {
        auto it = factors.begin();
        auto [first, cnt_first] = *it;
        int f = first;
        it = std::next(it);
        auto [second, cnt_second] = *it;
        int s = second;

        if (cnt_first < cnt_second) {
            swap(cnt_first, cnt_second);
            swap(f, s);
        }

        if (cnt_first >= 3) {
            a = first;
            b = second;
            c = n / (a * b);
        } else if (cnt_second >= 2) {
            a = first;
            b = second;
            c = n / (a * b);
        }
        else {
            std::cout << "NO\n";
            return;
        }
    }

    if (factors.size() >= 3) {
        auto it = factors.begin();
        a = it->first;
        it = std::next(it);
        b = it->first;
        c = n / (a * b);
    }

    std::cout << "YES\n";
    std::cout << a << ' ' << b << ' ' << c << '\n';
}