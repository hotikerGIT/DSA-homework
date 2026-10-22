// clang-format off
#include <bits/stdc++.h>
using namespace std;

using ll = long long; using ull = unsigned long long; using ld = long double;
using pii = pair<int, int>; using pll = pair<ll, ll>;
using vi = vector<int>; using vll = vector<ll>; using vvi = vector<vi>;

#define int long long
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
#define nn '\n'

template <class T> inline int sz(const T& x) { return (int)x.size(); }
template <class T> inline bool chmin(T& a, const T& b) { return a > b ? (a = b, true) : false; }
template <class T> inline bool chmax(T& a, const T& b) { return a < b ? (a = b, true) : false; }

constexpr int INF = 0x3f3f3f3f3f3f3f3f;
constexpr int MOD = 1000000007;

void solve();

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T = 1;
    // cin >> T;
    while (T--) solve();
}
// clang-format on
bool check(int x, short d) {
    if (d == 0) {
        return true;
    }
    for (int i = 0; i < 7; ++i) {
        if (x % 10 > d || x % 10 == 0) {
            return false;
        }
        x /= 10;
    }
    return true;
}

class LinearSieve {
private:
    std::vector<int> primes;
    std::vector<int> lp;
    int n;

public:
    LinearSieve(int size) : n(size) {
        lp.resize(n + 1, 0);

        for (int i = 2; i <= n; ++i) {
            if (lp[i] == 0) {
                lp[i] = i;
                primes.push_back(i);
            }

            for (int p : primes) {
                if (p > lp[i] || 1LL * i * p > n) break;
                lp[i * p] = p;
            }
        }
    }

    bool isPrime(int x) const {
        if (x < 2 || x > n) return false;
        return lp[x] == x;
    }

    std::vector<int> getPrimes() const {
        return primes;
    }

    int getLeastPrimeFactor(int x) const {
        if (x < 2 || x > n) return -1;
        return lp[x];
    }

    std::map<int, int> factorize(int x) const {
        std::map<int, int> factors;

        for (auto p : primes) {
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }

            if (cnt) factors[p] = cnt;


        }
        if (x > 1) factors[x] = 1;
        return factors;
    }

    void printPrimes() const {
        for (int p : primes) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
};

void solve() {
    int b;
    std::cin >> b;

    auto sieve = LinearSieve(1e6);  // достаточно для b <= 1e12

    auto f1 = sieve.factorize(b - 1);
    auto f2 = sieve.factorize(b);
    auto f3 = sieve.factorize(b + 1);

    std::set<int> pr_set;
    for (auto& [p, c] : f1) if (p < b) pr_set.insert(p);
    for (auto& [p, c] : f2) if (p < b) pr_set.insert(p);
    for (auto& [p, c] : f3) if (p < b) pr_set.insert(p);

    std::vector<int> primes(pr_set.begin(), pr_set.end());
    int res = 0;

    // стек хранит пары (индекс простого, текущее произведение)
    std::vector<std::pair<int, long long>> st;
    st.push_back({0, 1});

    while (!st.empty()) {
        auto [idx, prod] = st.back();
        st.pop_back();

        if (idx == (int)primes.size()) continue;

        // Вариант 0: пропустить текущее простое
        st.push_back({idx + 1, prod});

        // Варианты 1, 2, ...: умножить на текущее простое k раз
        long long cur = prod;
        while (true) {
            cur *= primes[idx];
            if (cur >= b) break;
            ++res;                          // нашли новое число < b
            st.push_back({idx + 1, cur});   // переходим к следующему простому
        }
    }

    std::cout << res;
}