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

bool check(std::string s, int p) {
    std::map<int, char> digit;
    std::map<char, int> chars;
    int index = s.size() - 1;

    while (p > 0) {
        int i = p % 10;
        p /= 10;

        if (chars.contains(s[index]) && chars[s[index]] != i) return false;
        if (digit.contains(i) && digit[i] != s[index]) return false;

        digit[i] = s[index];
        chars[s[index]] = i;
        index--;
    }

    return true;
}

int main() {
    std::string s;
    std::cin >> s;

    LinearSieve sieve = LinearSieve(1e7);

    int n = s.size();

    int left = 1;
    for (int i = 0; i < s.size() - 1; ++i) {
        left *= 10;
    }

    int right = left * 10;

    for (int p : sieve.getPrimes()) {
        if (p < left || p > right) continue;

        if (check(s, p)) {
            std::cout << p;
            return 0;
        }
    }

    std::cout << -1;
}