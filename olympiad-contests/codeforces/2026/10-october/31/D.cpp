#include <iostream>
#include <vector>
#include <map>
#define int long long

void solve() {
    int n;
    std::cin >> n;
    std::map<int, int> cnt;
    for (int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        cnt[a]++;
    }

    int oper = 0;
    int time = 0;

    while (cnt.size() != 1) {
        auto [min, min_cnt] = *cnt.begin();
        auto [max, max_cnt] = *cnt.rbegin();

        auto [min2, min2_cnt] = *(std::next(cnt.begin()));
        int first_cost = min_cnt * (min2 - min);
        int first_time = (min2 - min);

        auto [max2, max2_cnt] = *(std::next(cnt.rbegin()));
        int second_cost = max_cnt * (max - max2);
        int second_time = (max - max2);

        if (min_cnt < max_cnt) {
            cnt.erase(min);
            cnt[min2] += min_cnt;
            oper += first_cost;
            time += first_time;

        } else {
            cnt.erase(max);
            cnt[max2] += max_cnt;
            oper += second_cost;
            time += second_time;
        }
    }

    std::cout << oper << ' ' << time << std::endl;
}

signed main() {
    int t;
    std::cin >> t;
    while(t--) solve();
}