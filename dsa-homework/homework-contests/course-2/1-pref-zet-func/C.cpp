#include <iostream>
#include <ranges>
#include <vector>
#include <string>

std::vector<int> prefix_function(const std::string& s) {
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

    auto pf = prefix_function(s);

    std::vector<int> cnt(n + 1, 0);

    for (int i = 0; i < n; ++i) {
        cnt[pf[i]]++;
    }

    for (int i = n; i > 0; --i) {
        cnt[pf[i - 1]] += cnt[i];
    }

    std::vector<std::pair<int,int>> pref_cnt;
    for (int k = n; k > 0; k = pf[k - 1]) {
        pref_cnt.emplace_back(k, cnt[k]);
    }

    std::cout << pref_cnt.size() << '\n';
    for (auto & an : std::ranges::reverse_view(pref_cnt)) {
        std::cout << an.first << ' ' << an.second + 1 << '\n';
    }

    return 0;
}