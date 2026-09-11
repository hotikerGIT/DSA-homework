#include <iostream>
#include <ranges>
#include <vector>
#include <string>
#include <map>

std::vector<int> prefix_function(const std::vector<int>& s) {
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

    std::vector<int> sing(s.size() / 2);
    for (int i = 0; i < s.size(); i += 2) {
        sing[i / 2] = s[i] + s[i + 1];
    }

    auto pf = prefix_function(sing);
    std::cout << sing.size() - pf.back();
}