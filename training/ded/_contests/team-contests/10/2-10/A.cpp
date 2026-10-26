#include <iostream>
#include <vector>
#include <set>

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

    std::vector<int> factorize(int x) const {
        std::vector<int> factors;

        for (int i = 2; i * i <= x; ++i) {
            if (x % i == 0) {
                factors.push_back(i);
                factors.push_back(x / i);
            }
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

int main() {
    int n;
    std::cin >> n;

    std::vector<int> colors(n + 1, -1);
    colors[1] = 0;

    LinearSieve sieve(n + 1);
    for (int i = 2; i <= n; ++i) {
        auto factors = sieve.factorize(i);
        std::set<int> mex;

        for (auto factor : factors) {
            if (i == 100) {
                std::cout << factor << ' ';
            }
            mex.insert(colors[factor]);
        }

        for (int j = 1; j <= i + 1; ++j) {
            if (!mex.contains(j)) {
                colors[i] = j;
                break;
            }
        }
    }

    int max = 0;
    for (int color : colors) {
        max = std::max(max, color);
    }

    std::cout << max + 1 << std::endl;
    for (int i = 1; i < colors.size(); ++i) {
        std::cout << colors[i] + 1 << ' ';
    }
}