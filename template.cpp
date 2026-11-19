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

void solve() {
}