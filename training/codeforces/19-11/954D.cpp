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
    int n, m, s, t;
    cin >> n >> m >> s >> t;
    vector<set<int>> graph(n + 1);
    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        graph[a].insert(b);
        graph[b].insert(a);
    }

    vi dist_s(n + 1, 1e9), dist_t(n + 1, 1e9);

    auto bfs = [&](int start, vi& dist_arr) {
        queue<pii> q;
        q.emplace(start, 0);

        while (!q.empty()) {
            auto [cur, dist] = q.front();
            q.pop();

            if (dist >= dist_arr[cur]) continue;
            dist_arr[cur] = dist;

            for (int next : graph[cur]) q.emplace(next, dist + 1);
        }
    };
    bfs(s, dist_s);
    bfs(t, dist_t);

    int bad = 0;
    for (int v = 1; v <= n; ++v) {
        for (int u = v + 1; u <= n; ++u) {
            bad += !graph[v].contains(u) && (
                    dist_s[v] + dist_t[u] + 1 < dist_s[t] ||
                    dist_s[u] + dist_t[v] + 1 < dist_s[t]
                    );
        }
    }

    cout << n * (n - 1) / 2 - bad - m;
}