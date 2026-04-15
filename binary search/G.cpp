#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

bool check(int index, std::vector<int>& a, std::vector<int>& counter) {
    std::vector<int> check_counter(30);
    std::vector<int> indexes;
    for (int i = 0; i < 30 && index > 0; ++i) {
        check_counter[i] = std::min(index, counter[i]);
        index -= check_counter[i];

        if (check_counter[i]) {
            indexes.push_back(i);
        }
    }
    std::sort(indexes.begin(), indexes.end(), std::greater<int>());
    std::vector<int> ban;

    for (int num : a) {
        for (int ind : indexes) {
            int box = 1 << ind;

            int maximum = std::min(num / box, check_counter[ind]);
            check_counter[ind] -= maximum;
            num -= maximum * box;

            if (!check_counter[ind]) {
                ban.push_back(ind);
            }
        }

        for (int ind : ban) {
            indexes.erase(std::find(indexes.begin(), indexes.end(),ind));
        }
        ban.clear();
    }

    for (int count : check_counter) {
        if (count > 0) { return false; }
    }
    return true;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout.tie(0);

    int n, m, power;
    std::cin >> n >> m;

    std::vector<int> a(n);
    std::vector<int> counter(30);

    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    for (int i = 0; i < m; ++i) {
        std::cin >> power;
        counter[power]++;
    }
    std::sort(a.begin(), a.end());

    int left = 0;
    int right = m;
    int answer = 0;

    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (check(middle, a, counter)) {
            left = middle + 1;
            answer = middle;
        }
        else {
            right = middle - 1;
        }
    }

    std::cout << answer;
}