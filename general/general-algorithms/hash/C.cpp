#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#define int long long

const int p = 31;
const int mod = 1e9 + 9;
std::vector<int> powers;

std::vector<int> compute_hash(const std::string& s) {
    int n = s.size();
    std::vector<int> h(n + 1, 0);
    for (int i = 0; i < n; ++i) {
        h[i + 1] = (h[i] * p + (s[i] - 'a' + 1)) % mod;
    }
    return h;
}

int get_hash(const std::vector<int>& h, int l, int r) {
    int res = (h[r] - h[l - 1] * powers[r - l + 1]) % mod;
    if (res < 0) res += mod;
    return res;
}

bool is_palindrome(const std::vector<int>& hash_s, const std::vector<int>& hash_rev, int n, int l, int r) {
    int rev_l = n - r + 1;
    int rev_r = n - l + 1;
    return get_hash(hash_s, l, r) == get_hash(hash_rev, rev_l, rev_r);
}

int bin_search_odd(const std::vector<int>& hash_s, const std::vector<int>& hash_rev, int n, int center) {
    int left = 1, right = std::min(center - 1, n - center);
    int best = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int l = center - mid;
        int r = center + mid;
        if (is_palindrome(hash_s, hash_rev, n, l, r)) {
            best = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return best;
}

int bin_search_even(const std::vector<int>& hash_s, const std::vector<int>& hash_rev, int n, int center) {
    int left = 1, right = std::min(center, n - center);
    int best = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        int l = center - mid + 1;
        int r = center + mid;
        if (is_palindrome(hash_s, hash_rev, n, l, r)) {
            best = mid;
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return best;
}

signed main() {
    freopen("palindrome.in", "r", stdin);
    freopen("palindrome.out", "w", stdout);

    std::string s;
    std::cin >> s;
    int n = s.size();

    powers.resize(n + 5);
    powers[0] = 1;
    for (int i = 1; i < n + 5; ++i) powers[i] = (powers[i - 1] * p) % mod;
    std::vector<int> hash_s = compute_hash(s);
    std::string rev = s;
    std::reverse(rev.begin(), rev.end());
    std::vector<int> hash_rev = compute_hash(rev);

    int ans = 0;
    for (int center = 1; center <= n; ++center) ans += bin_search_odd(hash_s, hash_rev, n, center);
    for (int center = 1; center < n; ++center) ans += bin_search_even(hash_s, hash_rev, n, center);
    std::cout << ans << std::endl;
}