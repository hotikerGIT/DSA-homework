#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#define int long long

void solve(const std::vector<std::vector<int>>& basis) {
    int n;
    std::cin >> n;

    if (n == 1) {
        std::cout << -1 << '\n';
        return;
    }

    std::map<int, int> res;

    auto backtrack = [&](int num, int row_ind, int num_ind, auto&& self) -> bool {
        if (num == 1) return true;

        for (int i = row_ind; i >= 0; --i) {
            auto& row = basis[i];

            if (row.front() > num) continue;

            int start_j = i == row_ind ? num_ind : row.size() - 1;

            for (int j = start_j; j >= 0; --j) {
                int d = row[j];

                if (d > num) continue;

                if (num % d == 0) {
                    res[d]++;

                    if (self(num / d, i, j, self)) return true;

                    res[d]--;
                }
            }
        }

        return false;
    };

    if (backtrack(n, 17, basis.back().size() - 1, backtrack)) {
        int total = 0;
        for (auto& [num, cnt] : res) {
            total += cnt;
        }

        std::cout << total << '\n';
        for (auto& [num, cnt] : res) {
            for (int i = 0; i < cnt; ++i) {
                std::cout << num << ' ';
            }
        }
    } else {
        std::cout << -1;
    }

     std::cout << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;

    std::vector<std::vector<int>> basis(18);
    basis[0].push_back(6);
    basis[0].push_back(7);

    for (int i = 1; i < 18; ++i) {
        for (int num: basis[i - 1]) {
            int first = num * 10 + 6;
            int second = num * 10 + 7;
            basis[i].push_back(first);
            basis[i].push_back(second);
        }
    }

    while (t--) {
        solve(basis);
    }
}