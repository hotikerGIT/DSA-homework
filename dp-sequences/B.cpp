#include <iostream>
#include <vector>
#include <deque>

int lbs(std::vector<int>& vec, int target) {
    int left = 0;
    int right = (int)vec.size() - 1;

    while (left <= right) {
        int middle = (left + right) / 2;

        if (vec[middle] > target) {
            right = middle - 1;
        }

        else {
            left = middle + 1;
        }
    }

    return left;
}

int main() {
    int n;
    std::cin >> n;
    std::deque<int> a(n);
    int tmp;
    for (int i = 0; i < n; ++i) {
        std::cin >> tmp;
        a[i] = tmp;
    }

    std::vector<int> dp;
    dp.reserve(n);

    for (int num : a) {
        if (dp.empty() || dp.back() < num) {
            dp.push_back(num);
            continue;
        }

        int index = lbs(dp, num);
        dp[index] = num;
    }

    std::cout << dp.size();
}