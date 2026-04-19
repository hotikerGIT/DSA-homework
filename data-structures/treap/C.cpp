#include <bits/stdc++.h>

int main() {
    const int MOD = 1e9;
    int n;
    std::cin >> n;
    std::set<int> s;
    int last = 0;

    for (int i = 0; i < n; ++i) {
        char type;
        int a;
        std::cin >> type >> a;

        if (type == '+') {
            s.insert((a + last) % MOD);
            last = 0;
        }
        else {
            auto tmp = s.lower_bound(a);
            if (tmp == s.end()) last = -1;
            else last = *tmp;

            std::cout << last << '\n';
        }
    }
}