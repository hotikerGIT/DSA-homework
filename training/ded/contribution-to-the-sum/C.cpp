#include <iostream>
#include <vector>
#include <map>
#define int long long

int bin_pow(int number, int power, int mod) {
    if (power == 0) return 1;
    if (power % 2 == 1) return number * bin_pow(number, power - 1, mod) % mod;
    int half = bin_pow(number, power / 2, mod);
    return half * half % mod;
}


signed main() {
    int n;
    std::cin >> n;
    std::map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        cnt[a]++;
    }

    int ans = 0;
    int mod = 1e9 + 7;

    for (auto& [num, times] : cnt) {
        ans = (ans + bin_pow(2, n - times, mod) * (bin_pow(2, times, mod) - 1)) % mod;
    }

    std::cout << ans;
    return 0;
}