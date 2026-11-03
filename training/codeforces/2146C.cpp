#include <iostream>
#include <vector>
#include <string>

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> p(n);
    for (int i = 0; i < n; ++i) p[i] = i + 1;

    int left = 0;
    int right = 0;
    while (right < n) {
        while (right < n && s[right] == '1') {
            ++left;
            ++right;
        }
        if (right == n) break;

        while (right < n && s[right] != '1') right++;

        if (right - left == 1) {
            std::cout << "NO\n";
            return;
        }

        int min = left + 1;
        while (left < right) {
            if (p[left] == p[right - 1]) {
                p[left] = min;
            } else {
                p[left]++;
            }

            ++left;
        }
    }

    std::cout << "YES\n";
    for (int num : p) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while(t--) solve();
}