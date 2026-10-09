#include <iostream>
#include <vector>
#include <set>
#include <map>

int p = 37, mod = 1e9 + 9;
std::vector<int> powers;

int compute_hash(const std::set<int>& s) {
    int n = s.size();
    std::vector<int> forward_hash(n + 1, 0);
    int i = 0;
    for (int it : s) {
        forward_hash[i + 1] = (forward_hash[i] * p + (it - 'a' + 1)) % mod;
        i += 1;
    }
    return forward_hash.back();
}

void prepare(int power, int modulo, int length = 1e5) {
    p = power; mod = modulo;
    powers.resize(length + 1, 1);
    for (int i = 1; i <= length; ++i) {
        powers[i] *= powers[i - 1] * power;
        powers[i] %= modulo;
    }
}

void solve() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::set<int> nxt;
    std::map<int, int> hashes;
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                nxt.insert(a[i] ^ a[j]);

                auto it = nxt.end();
                if (nxt.size() > n) nxt.erase(std::prev(it));
            }
        }

        int hash = compute_hash(nxt);
        if (hashes.contains(hash)) break;
        hashes[hash] = *nxt.rbegin() - *nxt.begin();
    }

    for (int i = 0; i < q; ++i) {
        int x;
        if (x < )
    }
}

int main() {
    prepare(p, mod, 2e4);
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}