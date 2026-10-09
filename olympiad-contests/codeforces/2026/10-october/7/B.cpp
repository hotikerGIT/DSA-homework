#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void solve() {
    int n;
    std::string s;
    std::cin >> n >> s;

    std::vector<int> stack, res;
    for (int i = 1; i < s.size() + 1; ++i) {
        int ind = i - 1;

        if (s[ind] == '1') stack.push_back(i);
        if (s[ind] == '2') {
            if (!stack.empty()) {
                stack.pop_back();
                res.push_back(i);
            }
        }
    }

    if (!stack.empty()) {
        for (int num : stack) {
            res.push_back(num);
        }
    }
    std::sort(res.begin(), res.end());

    std::cout << res.size() << std::endl;
    for (int num : res) std::cout << num << ' ';
    std::cout << '\n';
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}