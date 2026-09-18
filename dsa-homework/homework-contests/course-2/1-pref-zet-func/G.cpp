#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    std::string s;
    std::cin >> s;
    int n = s.size();

    std::vector<int> dp(n + 1, 1e9);
    dp[0] = 0;

    std::string suffix;

    for (int i = 0; i < s.size(); ++i) {
        suffix = s[i] + suffix;

        auto pf = prefix_function(suffix);
        for (int j = 0; j < pf.size(); ++j) {
            int p = (j + 1) - pf[j];
            if ((j + 1) % p != 0) p = j + 1;
            int cnt = (j + 1) / p;
            int next = p + std::to_string(cnt).size() + dp[i + 1 - p * cnt];
            dp[i + 1] = std::min(dp[i + 1], next);
        }
    }

    std::cout << dp[n];
}