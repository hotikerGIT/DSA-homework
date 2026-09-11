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
    int n, w;
    std::cin >> n >> w;
    std::vector<int> a(n), b(w), da(n - 1), db(w - 1);

    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < w; ++i) std::cin >> b[i];

    for (int i = 0; i < n - 1; ++i) da[i] = a[i + 1] - a[i];
    for (int i = 0; i < w - 1; ++i) db[i] = b[i + 1] - b[i];

    std::vector<int> cmp(n + w - 1);
    for (int i = 0; i < w - 1; ++i) cmp[i] = db[i];
    cmp[w - 1] = 2e9;
    for (int i = w; i < n + w - 1; ++i) cmp[i] = da[i - w];

    auto pf = prefix_function(cmp);

    int res = 0;
    for (int len : pf) {
        res += len >= w - 1;
    }

    std::cout << res;
}