#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

struct Interval {
    int start = -1, end = -1;

    int size() {
        return end - start + 1;
    }
};

void solve() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::vector<Interval> intervals(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
    }

    int start = 1e16;
    int value = 0;

    Interval right = Interval();
    Interval left = intervals.back();
    Interval check = Interval(start, start + m - 1);

    for (int cur = intervals.size() - 1; cur >= 0;) {
        int a =left.end;
        int b =right.start - m + 1;

        if (a <= b) {
            if (k <= value && value - (check.end - right.start) <= k) {
                std::cout << "a";
            }
        }

        else {

        }
    }
}

signed main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}