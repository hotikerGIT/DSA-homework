#include <iostream>
#include <string>


void solve() {
    int n; char c; std::string s;
    std::cin >> n >> c >> s;

    int left = 0;
    int right = s.size() - 1;
    int cost = 0;
    for (; left < right; ++left, --right) {
        if (s[left] == s[right]) continue;
        cost += s[left] != c;
        cost += s[right] != c;
    }

    std::cout << cost << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}