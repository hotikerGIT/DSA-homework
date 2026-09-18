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

bool check(std::string s, int cnt, int assume) {
    if (assume == 0) return true;

    std::string p = s.substr(0, assume) + '#' + s;
    auto pf = prefix_function(p);

    int inside = 0;
    for (int i = 0; i < pf.size(); ++i) {
        if (pf[i] == assume) {
            inside++;
            i += assume - 1;
        }
    }

    return inside >= cnt;
}

void solve() {
    int n, l, r;
    std::string s;
    std::cin >> n >> l >> r >> s;

    int left = 0;
    int right = s.size();
    int ans = 0;

    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(s, l, mid)) {
            left = mid + 1;
            ans = mid;
        } else {
            right = mid - 1;
        }
    }

    std::cout << ans << '\n';
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        solve();
    }
}