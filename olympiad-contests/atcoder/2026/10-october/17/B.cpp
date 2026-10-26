#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <string>
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

int match(const std::vector<std::string>& candidates, const std::string& ballot) {
    std::vector<int> error(candidates.size(), -1);

    for (int i = 0; i < candidates.size(); ++i) {
        auto& candidate = candidates[i];

        if (candidate.size() != ballot.size()) continue;

        int miss = 0;
        for (int j = 0; j < ballot.size(); ++j) {
            miss += candidate[j] != ballot[j];
        }

        error[i] = miss;
    }

    for (int i = 0; i < error.size(); ++i) {
        if (error[i] == 0) return i;
    }

    int index = -1;
    for (int i = 0; i < error.size(); ++i) {
        if (error[i] == 1) {
            if (index == -1) index = i;
            else return -1;
        }
    }

    return index;
}

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> candidates(n), ballots(m);
    for (int i = 0; i < n; ++i) std::cin >> candidates[i];
    for (int i = 0; i < m; ++i) std::cin >> ballots[i];

    std::vector<int> cnt(n);

    for (auto& ballot : ballots) {
        int index = match(candidates, ballot);

        if (index != -1) cnt[index]++;
    }

    for (int num : cnt) {
        std::cout << num << '\n';
    }
}