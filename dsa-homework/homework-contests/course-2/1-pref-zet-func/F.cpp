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
    std::string s, t;
    std::cin >> s >> t;

    auto pf_t = prefix_function(t);
    int lowest_cycle = t.size() - pf_t.back();

    int cycle0 = 0, cycle1 = 0;
    for (int i = 0; i < lowest_cycle; ++i) {
        cycle0 += t[i] == '0';
        cycle1 += t[i] == '1';
    }

    int s0 = 0, s1 = 0;
    for (char c : s) {
        s0 += c == '0';
        s1 += c == '1';
    }

    std::string res;
    int cur = 0;
    for (int i = 0; i < s.size(); ++i) {
        if (t[cur] == '0' && s0 || !s1) {
            res += '0';
            s0--;
        } else {
            res += '1';
            s1--;
        }

        cur++;
        cur %= lowest_cycle;
    }

    std::cout << res;
}