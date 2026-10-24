#include <iostream>
#include <vector>
#include <string>

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
    std::string s, q;
    std::cin >> s >> q;

    auto pf = prefix_function(q);
    std::vector dp(s.size() + 1, std::vector<int>(2, 0));

    for (int i = 1; i < s.size() + 1; ++i) {
        int k = dp[i - 1][0];
        if (k == q.size()) break;

        while (k > 0 && q[k] != s[i - 1]) k = pf[k - 1];
        if (q[k] == s[i - 1]) dp[i][0] = k + 1;

        k = dp[i - 1][1];
        if (k == q.size()) break;

        while (k > 0 && q[k] != s[i - 1]) k = pf[k - 1];
        if (q[k] == s[i - 1]) dp[i][1] = k + 1;

        dp[i][1] = std::max(dp[i][1], dp[i - 1][0] + 1);
    }

    for (int i = 1; i < dp.size(); ++i) {
        if (dp[i][0] == q.size() || dp[i][1] == q.size()) {
            std::cout << i - q.size() + 1;
            return 0;
        }
    }

    std::cout << 0;
}