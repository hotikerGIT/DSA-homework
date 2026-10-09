#include <iostream>
#include <vector>
#include <map>
#define int long long

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
        while (x > 1) {
            int p = lp[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            factors[p] = cnt;
        }
        return factors;
    }

    void printPrimes() const {
        for (int p : primes) {
            std::cout << p << " ";
        }
        std::cout << std::endl;
    }
};

void solve(LinearSieve& sieve) {
    int n, x;
    std::cin >> n >> x;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    auto factors = sieve.factorize(x);
    std::map<int, int> sum_by_factor;

    for (int num : a) {
        auto num_factors = sieve.factorize(num);

        for (auto& [factor, cnt] : num_factors) {
            if (factors.contains(factor)) sum_by_factor[factor] += num;
        }
    }

    int res = 0;
    for (auto& [factor, sum] : sum_by_factor) res = std::max(res, sum);
    std::cout << res << '\n';
}

signed main() {
    LinearSieve sieve(3e5 + 5);
    int t;
    std::cin >> t;
    while (t--) {
        solve(sieve);
    }
}