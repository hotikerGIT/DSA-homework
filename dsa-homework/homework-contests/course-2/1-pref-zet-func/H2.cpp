#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

std::vector<int> z_function(const std::string& s) {
    int n = (int)s.size();
    std::vector<int> z(n);
    z[0] = n;

    int l = 0, r = 0;

    for (int i = 1; i < n; ++i) {
        if (i <= r) z[i] = std::min(r - i + 1, z[i - l]);

        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) ++z[i];

        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }

    return z;
}

bool check(const std::vector<int>& z, int n, int cnt, int assume) {
    if (assume == 0) return true;

    int inside = 0;
    int i = 0;
    while (i < n) {
        if (z[i] >= assume) {
            ++inside;
            i += assume;
        } else {
            ++i;
        }
    }

    return inside >= cnt;
}

void solve() {
    int n, l, r;
    std::string s;
    std::cin >> n >> l >> r >> s;
    std::vector<int> res(n + 1, 0);

    auto z = z_function(s);

    int cur = 1;
    for (; cur * cur <= n; ++cur) {
        int left = 0;
        int right = n;
        int ans = 0;

        while (left <= right) {
            int mid = (left + right) / 2;

            if (check(z, n, cur, mid)) {
                left = mid + 1;
                ans = mid;
            } else {
                right = mid - 1;
            }
        }

        res[cur] = ans;
    }

    for (int len = ceil(sqrt(n)); len > 0; --len) {
        int inside = 0;
        int i = 0;

        while (i < n) {
            if (z[i] >= len) {
                ++inside;
                i += len;
            } else {
                ++i;
            }
        }

        for (; cur <= inside; ++cur) {
            res[cur] = len;
        }
    }

    for (int i = l; i <= r; ++i) {
        std::cout << res[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}