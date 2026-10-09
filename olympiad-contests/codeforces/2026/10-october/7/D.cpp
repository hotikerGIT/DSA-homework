#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

int cost(std::vector<int>& lab, int want) {
    int sum = lab[0] + lab[1] + lab[2];
    if (sum >= want) return 0;

    int difference = want - sum;
    int a = lab[1] - lab[0];
    int b = lab[2] - lab[1];

    if (a < 0 || b < 0) {
        return difference;
    }

    if (a == 0 && b == 0) return -1;

    return 2 * (std::min(a, b) + 1) + difference;
}

bool check(int assumption, std::vector<std::vector<int>>& labs, int k) {
    for (auto& lab : labs) {
        int c = cost(lab, assumption);

        if (c == -1) return false;

        k -= c;

        if (k < 0) return false;
    }

    return true;
}

void solve() {
    int n, k;
    std::cin >> n >> k;
    std::vector<std::vector<int>> labs(n);

    for (int i = 0; i < n; ++i) {
        int a, b, c;
        std::cin >> a >> b >> c;
        auto& last = labs[i];
        last.push_back(a);
        last.push_back(b);
        last.push_back(c);
    }

    int left = -4e18;
    int right = 4e18;
    int ans = -2e18;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(mid, labs, k)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    std::cout << ans << '\n';
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}