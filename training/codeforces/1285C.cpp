#include <iostream>
#include <vector>
#include <map>
#define int long long

int bin_pow(int num, int power) {
    if (power == 0) return 1;
    if (power % 2 == 1) return num * bin_pow(num, power - 1);
    int half = bin_pow(num, power / 2);
    return half * half;
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

    std::map<int, int> factorize_big(int x) const {
        std::map<int, int> factors;

        for (int i = 2; i * i <= x; ++i) {
            while (x % i == 0) {
                factors[i]++;
                x /= i;
            }
        }

        if (x != 1) factors[x] = 1;
        return factors;
    }

    std::vector<std::pair<int, int>> factorize(int x) const {
        std::vector<std::pair<int, int>> factors;
        while (x > 1) {
            int p = lp[x];
            int cnt = 0;
            while (x % p == 0) {
                x /= p;
                cnt++;
            }
            factors.emplace_back(p, cnt);
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

signed main() {
    int x;
    std::cin >> x;

    auto sieve = LinearSieve(1e6);
    auto factors = sieve.factorize_big(x);

    std::vector<int> different_factors;
    for (auto& [factor, cnt] : factors)
        different_factors.push_back(factor);

    int size = different_factors.size();
    int ans = 1e13;
    int best_a = 1e13;
    int best_b = 1e13;
    for (int mask = 0; mask < 1 << size; ++mask) {
        int a = 1;
        int b = 1;

        for (int i = 0; i < size; ++i) {
            int factor = different_factors[i];
            int more = bin_pow(factor, factors[factor]);
            if ((mask >> i) & 1) {
                a *= more;
            } else {
                b *= more;
            }
        }

        if (std::max(a, b) < ans) {
            ans = std::max(a, b);
            best_a = a;
            best_b = b;
        }
    }

    std::cout << best_a << ' ' << best_b;
}