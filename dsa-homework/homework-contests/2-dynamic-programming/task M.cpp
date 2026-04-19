#include <iostream>
#include <vector>
#include <algorithm>

typedef long long ll;
int main() {
    ll n, m, b, mod;
    std::cin >> n >> m >> b >> mod;

    std::vector<ll> a(n);
    for (ll i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::sort(a.begin(), a.end());

    // key is amount of coins, value is frequency
    std::vector<std::vector<ll>> first_gen(b + 1, std::vector<ll>(m + 1, 0));
    std::vector<std::vector<ll>> second_gen(b + 1, std::vector<ll>(m + 1, 0));
    first_gen[0][0] = 1;

    ll amount, frequency;
    ll coin;

    ll res = 0;
    for (ll i = 0; i < n; ++i) {
        coin = a[i];
        second_gen.clear();
        second_gen.resize(b + 1);

        for (ll j = 0; j <= b; ++j) {
            second_gen[j] = first_gen[j];

            if (j < coin) {
                continue;
            }

            for (int k = 0; k < m; ++k) {
                amount = k;
                frequency = second_gen[j - coin][k];

                if (!frequency) {
                    continue;
                }

                second_gen[j][amount + 1] = (second_gen[j][amount + 1] + frequency) % mod;
            }
        }

        std::swap(first_gen, second_gen);
    }

    for (ll i = 0; i <= b; ++i) {
        res = (res + first_gen[i][m]) % mod;
    }

    std::cout << res % mod;
}