#include <iostream>
#include <string>
#include <set>

void solve();

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::set<int> ind;
    for (int i = 0; i < s.size(); ++i) {
        if (s[i] == '1') ind.insert(i);
    }

    if (ind.size() >= 3) {
        std::cout << *ind.rbegin() - *ind.begin();
    } else if (ind.size() == 2) {
        std::cout << 1;
    } else {
        std::cout << 0;
    }

    std::cout << '\n';
}