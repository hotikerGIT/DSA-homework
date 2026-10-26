#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#define int long long

void solve();

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t = 1;
    //std::cin >> t;
    while (t--) solve();
}

void solve() {
    char c11, c12, c21, c22;
    std::cin >> c11 >> c12 >> c21 >> c22;

    if (c11 == 'A' && c22 == 'D' ||
        c11 == 'D' && c22 == 'A' ||
        c12 == 'A' && c21 == 'D' ||
        c12 == 'D' && c21 == 'A') {
        std::cout << "No";
    } else {
        std::cout << "Yes";
    }
}