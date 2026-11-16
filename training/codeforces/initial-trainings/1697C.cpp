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
     cin >> T;
    while (T--) solve();
}
// clang-format on

void solve() {
    int n;
    string s, t;
    cin >> n >> s >> t;

    vi s_order, t_order;
    for (int i = 0; i < n; ++i) {
        if (s[i] == 'a') s_order.push_back(0);
        if (s[i] == 'c') s_order.push_back(1);
        if (t[i] == 'a') t_order.push_back(0);
        if (t[i] == 'c') t_order.push_back(1);
    }

    map<char, vi> s_ind;
    map<char, vi> t_ind;

    int sa_cnt = 0;
    int sb_cnt = 0;
    int ta_cnt = 0;
    int tb_cnt = 0;

    for (int i = 0; i < n; ++i) {
        if (s[i] == 'b') s_ind['b'].push_back(sa_cnt);
        if (t[i] == 'b') t_ind['b'].push_back(ta_cnt);

        if (s[i] == 'c') s_ind['c'].push_back(sb_cnt);
        if (t[i] == 'c') t_ind['c'].push_back(tb_cnt);

        sa_cnt += s[i] == 'a';
        sb_cnt += s[i] == 'b';
        ta_cnt += t[i] == 'a';
        tb_cnt += t[i] == 'b';
    }

    if (sa_cnt != ta_cnt || sb_cnt != tb_cnt) {
        cout << "NO" << nn;
        return;
    }

    for (int i = 0; i < s_order.size(); ++i) {
        if (s_order[i] != t_order[i]) {
            cout << "NO" << nn;
            return;
        }
    }

    for (int i = 0; i < s_ind['b'].size(); ++i) {
        if (s_ind['b'][i] < t_ind['b'][i]) {
            cout << "NO" << nn;
            return;
        }
    }

    for (int i = 0; i < s_ind['c'].size(); ++i) {
        if (s_ind['c'][i] < t_ind['c'][i]) {
            cout << "NO" << nn;
            return;
        }
    }

    cout << "YES" << nn;
}