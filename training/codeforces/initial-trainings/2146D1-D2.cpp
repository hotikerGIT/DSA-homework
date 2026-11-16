// clang-format off
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;

#define int unsigned long long

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
    int l, r;
    cin >> l >> r;
    vi a(r - l + 1);
    iota(all(a), l);

    map<int, int> ans;

    auto check_power = [&]() {
        int width = bit_width(a[0]);

        for (int num : a) {
            if (bit_width(num) != width) return false;
        }
        return true;
    };

    int lazy = 0;
    while (a.size() > 1) {
        while (check_power()) {
            int power = (1 << (bit_width(a[0]) - 1));
            lazy |= power;

            for (int& num : a) num -= power;
        }

        int power = bit_width(a.back()) - 1;
        int index = a.size() - 1 - (a.back() - (1 << power));

        int half = min(index, a.size() - index);

        for (int i = 0; i < half; ++i) {
            ans[a[index + i] + lazy] = lazy + a[index - 1 - i];
            ans[lazy + a[index - 1 - i]] = a[index + i] + lazy;
        }

        vi tmp;

        for (int i = index + half; i < a.size(); ++i) tmp.push_back(a[i]);
        for (int i = 0; i < index - half; ++i) tmp.push_back(a[i]);

        swap(tmp, a);
    }

    if (!a.empty()) {
        ans[a[0] + lazy] = a[0] + lazy;
    }

    int sum = 0;
    for (auto& [ind, val] : ans) sum += ind | val;
    cout << sum << nn;
    for (auto& [ind, val] : ans) cout << val << ' ';
    cout << nn;
}