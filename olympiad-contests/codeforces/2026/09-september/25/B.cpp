#include <iostream>
#include <vector>
#include <algorithm>

void solve() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    std::vector<int> cnt(105);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        cnt[a[i]]++;
    }

    std::sort(a.begin(), a.end());

    std::vector<int> res(n);

    int index = 0;
    while (index < n) {
        int max = 0;
        for (int num = 100; num >= 0; --num) {
            if (cnt[num]) {
                max = num;
                break;
            }
        }

        int max_cnt = 0;
        while (cnt[max]) {
            res[index] = max;
            cnt[max]--;
            index++;
            max_cnt++;
        }

        for (int num = max - 1; num > 0; --num) {
            int cur_cnt = 0;

            while (cnt[num] && cur_cnt < max_cnt) {
                res[index] = num;
                cnt[num]--;
                index++;
                cur_cnt++;
            }
        }
    }

    for (int num : res) {
        std::cout << num << ' ';
    }

    std::cout << '\n';
}

int main() {
    int t;
    std::cin >> t;
    while (t--) {
        solve();
    }
}