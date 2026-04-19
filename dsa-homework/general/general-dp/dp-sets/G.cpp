#include <iostream>
#include <vector>

typedef long long ll;
const ll MOD = 1000000007;

ll pow_mod(ll a, ll b, ll mod) {
    ll res = 1;
    while (b > 0) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

ll comb(ll n, ll k, ll mod) {
    if (k < 0 || k > n) return 0;
    if (k == 0 || k == n) return 1;
    if (k > n - k) k = n - k;
    
    ll numerator = 1;
    ll denominator = 1;
    
    for (ll i = 0; i < k; i++) {
        numerator = (numerator * ((n - i) % mod)) % mod;
        denominator = (denominator * (i + 1)) % mod;
    }
    
    return (numerator * pow_mod(denominator, mod - 2, mod)) % mod;
}

int main() {
    ll n, s;
    std::cin >> n >> s;
    
    std::vector<ll> f(n);
    for (int i = 0; i < n; i++) {
        std::cin >> f[i];
    }

    ll result = 0;

    for (int mask = 0; mask < (1 << n); mask++) {
        ll sum = 0;
        int bits = 0;

        for (int i = 0; i < n; i++) {
            if (mask & (1 << i)) {
                sum += f[i] + 1;
                bits++;
            }
        }

        if (sum > s) continue;

        ll remaining = s - sum;
        ll ways = comb(remaining + n - 1, n - 1, MOD);

        if (bits % 2 == 0) {
            result = (result + ways) % MOD;
        } else {
            result = (result - ways + MOD) % MOD;
        }
    }

    std::cout << result;
}