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
    std::cin >> n;
    vector matrix(2, vector<char>(n));
    for (auto& row : matrix) for (auto& ch : row) std::cin >> ch;

    vector visited(2, vector(n, vector<int>(2)));
    queue<vi> q;
    vi start = {0, 0, 0};
    q.push(start);

    while (!q.empty()) {
        auto state = q.front();
        q.pop();

        int i = state[0];
        int j = state[1];
        int type = state[2];

        if (i < 0 || i >= 2 || j < 0 || j >= n) continue;
        if (visited[i][j][type]) continue;
        visited[i][j][type] = 1;

        if (type == 0) {
            type = 1 - type;

            vi s1 = {i + 1, j, type};
            vi s2 = {i - 1, j, type};
            vi s3 = {i, j + 1, type};
            vi s4 = {i, j - 1, type};

            q.push(s1);
            q.push(s2);
            q.push(s3);
            q.push(s4);
        } else {
            type = 1 - type;

            vi s;

            if (matrix[i][j] == '>') {
                s = {i, j + 1, type};
            } else {
                s = {i, j - 1, type};
            }

            q.push(s);
        }
    }

    if (visited.back().back()[0] || visited.back().back()[1]) {
        std::cout << "YES\n";
    } else {
        std::cout << "NO\n";
    }
}