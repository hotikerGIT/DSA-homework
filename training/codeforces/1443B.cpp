#include <iostream>
#include <vector>
#include <string>
#define int long long

void solve() {
    int a, b;
    std::string s;
    std::cin >> a >> b >> s;
    int n = s.size();

    std::string t;
    int first = -1;
    int second = -1;
    for (int i = 0; i < n; ++i) {
        if (s[i] == '0') continue;
        first = i;
        break;
    }

    for (int i = n - 1; i >= 0; --i) {
        if (s[i] == '0') continue;
        second = i;
        break;
    }

    if (first == -1) {
        std::cout << 0 << '\n';
        return;
    }

    for (int i = first; i <= second; ++i) t += s[i];

    std::vector<int> dist;
    for (int i = 0; i < t.size(); ++i) {
        if (t[i] == '1') continue;

        if (t[i - 1] == '1') {
            dist.push_back(1);
        } else {
            dist[dist.size() - 1]++;
        }
    }

    std::vector<int> dp(dist.size() + 1);
    dp[0] = a;
    for (int i = 1; i < dp.size(); ++i) {
        dp[i] = dp[i - 1] + std::min(a, b * dist[i - 1]);
    }

    std::cout << dp.back() << '\n';
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}