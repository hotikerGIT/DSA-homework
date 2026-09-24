#include <iostream>
#include <vector>
#include <map>
#include <cmath>
#define int long long

int max_bit(int num) {
    int j = 0;
    for (; num > 0; ++j) num >>= 1;
    return j;
}

int cost(int number) {
    if (number <= 1) return 1;
    return 1 << (number - 1);
}

bool check(std::map<int, int>& st, int assumption) {
    int free = 0;
    int need = assumption;
    int max_i = st.rbegin()->first;

    for (int i = max_i; i >= 0; --i) {
        int cnt_i = 0;
        auto it = st.find(i);
        if (it != st.end()) cnt_i = it->second;

        if (cnt_i < need) {
            need += need - cnt_i;
        } else {
            free += cnt_i - need;
        }
    }

    return need <= free + st[0];
}

void solve() {
    int n;
    std::cin >> n;
    std::map<int, int> st;

    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        st[x] = y;
    }

    int max = st.rbegin()->first;

    if (st.rbegin()->first > 2e5 + 60) {
        std::cout << max << '\n';
        return;
    }

    int left = 0;
    int right = 1e9;
    int ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (check(st, mid)) {
            ans = mid;
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }

    if (!ans) {
        std::cout << max << std::endl;
        return;
    }

    int add = 0;
    for (; cost(add) <= ans; ++add) {}

    std::cout << max + add << std::endl;
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}