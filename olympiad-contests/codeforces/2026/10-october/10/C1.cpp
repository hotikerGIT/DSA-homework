#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> operator+(const std::vector<int>& a, const std::vector<int>& b) {
    std::vector<int> res;

    for (int num : a) {
        res.push_back(num);
    }

    for (int num : b) {
        res.push_back(num);
    }

    return res;
}

void solve() {
    int n;
    std::cin >> n;

    int index = std::floor(std::log2(n)) + 1;
    std::vector<int> out;
    out.reserve(2 * n);
    out.push_back(0);
    out.push_back(1);
    out.push_back(0);

    int cur = 1;
    while (cur < index) {
        out.push_back(1 << cur);

        int sz = out.size() - 1;
        for (int i = 0; i < sz; ++ i) {
            out.push_back(out[i]);
        }
        ++cur;
    }

    std::cout << out.size() << std::endl;
    for (int num : out) {
        std::cout << num << ' ';
    }
    std::cout << std::endl;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) solve();
}