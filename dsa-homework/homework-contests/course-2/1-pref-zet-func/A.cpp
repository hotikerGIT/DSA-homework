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
    std::string s;
    std::cin >> s;

    auto pf = prefix_function(s);
    long long res = 0;

    for (int num : pf) {
        res += num;
    }

    std::cout << res;
}