#include <iostream>
#include <vector>
#include <string>
#include <map>

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

std::vector<int> prefix_function(std::string s) {
    std::vector<int> pref_func(s.size());

    for (int i = 1; i < s.size(); ++i) {
        int p = pref_func[i - 1];

        while (p > 0 && s[p] != s[i]) p = pref_func[p - 1];

        if (s[p] == s[i]) {
            pref_func[i] = p + 1;
        }
    }

    return pref_func;
}

int main() {
    std::string s1, s2, s;
    std::cin >> s1 >> s2;
    s = s1 + s2;

    auto pf_s = prefix_function(s);
    int lowest_cycle = s.size() - pf_s.back();

    if (lowest_cycle < 0 || s1.size() % lowest_cycle != 0 || s2.size() % lowest_cycle != 0) {
        std::cout << 0;
        return 0;
    }

    LinearSieve sieve = LinearSieve(1e5 + 5);
    auto map1 = sieve.factorize(s1.size() / lowest_cycle);
    auto map2 = sieve.factorize(s2.size() / lowest_cycle);

    int ans = 1;
    for (auto [prime, cnt] : map1) {
        ans *= std::min(cnt, map2[prime]) + 1;
    }

    std::cout << ans;
}