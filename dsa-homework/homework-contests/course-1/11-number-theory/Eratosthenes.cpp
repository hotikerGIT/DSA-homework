#include <iostream>
#include <vector>

using namespace std;

vector<bool> naive(int n) {
    vector<bool> primes(n + 1, true);
    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i <= n; ++i) {
        if (primes[i]) for (int j = 2; j * i <= n; ++j) primes[j * i] = false;
    }

    return primes;
}

vector<bool> better(int n) {
    vector<bool> primes(n + 1, true);
    primes[0] = false;
    primes[1] = false;

    for (int i = 2; i * i <= n; ++i) {
        if (primes[i]) for (int j = i; j * i <= n; ++j) primes[j * i] = false;
    }

    return primes;
}

vector<int> best(int n) {
    vector<int> least_prime_factor(n + 1, 0);
    vector<int> primes;

    for (int i = 2; i <= n; ++i) {
        if (least_prime_factor[i] == 0) {
            least_prime_factor[i] = i;
            primes.push_back(i);
        }

        for (int p : primes) {
            if (p > least_prime_factor[i] || p * i > n) break;
            least_prime_factor[p * i] = p;
        }
    }

    return primes;
}

void check(vector<bool>& c) {
    for (int i = 0; i < c.size(); ++i) {
        if (c[i]) std::cout << i << ' ';
    }
    std::cout << endl;
}

int main() {
    vector<int> c = best(1e7);
    for (int num : c) std::cout << num << ' ';
}