#include <iostream>
#include <vector>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto& num : a) std::cin >> num;

    int best = 0;
    for (int num : a) {
        int cnt = 0;

        for (int i : a) {
            cnt += i % num == 0;
        }

        best = std::max(best, cnt);
    }

    std::cout << n - best << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}