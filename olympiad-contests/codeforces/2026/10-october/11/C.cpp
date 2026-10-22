#include <iostream>
#include <vector>
#include <set>

void solve();

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}

void decode(const std::vector<int>& res) {
    std::vector<int> out(res.size());

    int cur = 0;
    for (int i = 0; i < res.size(); ++i) {
        for (int j = 0; j < res[i]; ++j) {
            out[cur] = i + 1;
            ++cur;
        }
    }

    for (auto num : out) {
        std::cout << num << ' ';
    }
}

std::pair<int, int> trying(int n, int k, bool to_print = false) {
    std::vector<int> res(n);

    int cur = 0;
    int total = 0;
    for (int i = k; i > 0; --i) {
        int sum = 0;
        while (cur < n && total + i <= n && sum + i <= k) {
            res[cur] = i;
            ++cur;
            sum += i;
            total += i;
        }
    }

    int r = n - total;
    res[cur] = r;

    std::vector<int> cnt(n);
    for (int num: res) {
        cnt[num]++;
    }

    int ans = 0;
    for (int i = 1; i <= n; ++i)
        ans = std::max(ans, i * cnt[i]);

    if (to_print) {
        std::cout << ans << std::endl;

        decode(res);

        std::cout << std::endl;
    }

    return {ans, k};
}

void solve() {
    int n;
    std::cin >> n;

    std::set<std::pair<int, int>> k_vals;
    for (int k = 1; k < std::min(n, 10000); ++k) {
        k_vals.insert(trying(n, k));
    }

    auto it = k_vals.begin();
    trying(n, it->second, true);
}