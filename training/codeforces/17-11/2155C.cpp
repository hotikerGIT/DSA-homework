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
void test();

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    test();

//    int T = 1;
//     cin >> T;
//    while (T--) {
//        solve();
//        cout << nn;
//    }
}
// clang-format on

void test() {
    int n = 20;
    map<int, int> hash_cnt;
    set<string> out;

    for (int mask = 0; mask < 1 << n; ++mask) {
        vi t(n);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                int bit = (mask >> j) & 1;

                t[i] += !bit && i >= j;
                t[i] += bit && i <= j;
            }
        }

        string sout;
        for (int i = 1; i < n; ++i) sout += to_string(t[i] - t[i - 1]) + ' ';
        out.insert(sout);
        int hash = 0;
        for (int num : t) {
            hash *= 10;
            hash += num;
//            cout << num << ' ';
        }
        hash_cnt[hash]++;
//        cout << nn;
    }

    for (auto& [hash, cnt] : hash_cnt) {
//        cout << hash << ' ' << cnt << nn;

        if (cnt > 1) {
            cout << "CNT = " << cnt << " ON HASH " << hash << nn;
        }
    }

    cout << out.size() << nn;
    for (auto& s : out) cout << s << nn;
}

void solve() {
    int n;
    cin >> n;
    vi a(n);
    get_vector(a);

    vi comp_diff;
    for (int i = 1; i < n; ++i) {
        int diff = a[i] - a[i - 1];

        if (comp_diff.empty() || comp_diff.back() != diff)
            comp_diff.push_back(diff);
    }

    if (comp_diff.size() == 1 && comp_diff[0] == 0 && n % 2 == 1 && a[0] == n / 2 + 1) {
        cout << 2;
        return;
    }

    for (int num : comp_diff) if (abs(num) > 1) {
        cout << 0;
        return;
    }

    for (int i = 2; i < comp_diff.size(); ++i) {
        if (comp_diff[i] == 0) continue;

        if (abs(comp_diff[i]) != 1) {
            cout << 0;
            return;
        }

        if (comp_diff[i] != -comp_diff[i - 2]) {
            cout << 0;
            return;
        }
    }

    cout << 1;
}