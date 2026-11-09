#include <bits/stdc++.h>
using namespace std;

#define int long long

using vi = vector<int>; using vvi = vector<vi>;
using pii = pair<int, int>; using vpii = vector<pii>;

using H = decltype([](uint64_t x) {
    static const uint64_t r = chrono::steady_clock::now().time_since_epoch().count();
    x += r + 0x9e3779b97f4a7c15ULL; x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL; return x ^ (x >> 31);
});


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

void solve() {
    int n, m, l;
    cin >> n >> m >> l;
    vi a(n);
    get_vector(a, n);

    set<pair<int, int>> intervals;
    auto add_interval = [&](int left, int right, auto&& self) -> void {
        auto it = intervals.upper_bound({left, right});

        if (it != intervals.end()) {
            if (it->first - right == 1) {
                int new_left = left;
                int new_right = it->second;
                intervals.erase(it);

                self(new_left, new_right, self);
                return;
            }
        }

        if (it != intervals.begin()) {
            auto pr = prev(it);

            if (left - pr->second == 1) {
                int new_left = pr->first;
                int new_right = right;
                intervals.erase(pr);

                self(new_left, new_right, self);
                return;
            }
        }

        intervals.insert({left, right});
    };

    for (int i = 0; i < n; ++i) {
        if (a[i] > l) add_interval(i, i, add_interval);
    }

    for (int i = 0; i < m; ++i) {
        int t;
        cin >> t;

        if (t == 0) {
            std::cout << intervals.size() << '\n';
        } else {
            int p, d;
            cin >> p >> d;
            p--;

            if (a[p] <= l && a[p] + d > l) {
                add_interval(p, p, add_interval);
            }

            a[p] += d;
        }
    }
}