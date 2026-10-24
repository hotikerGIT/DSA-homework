#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

int main() {
    std::random_device rd;
    std::mt19937 g(rd());

    int k;
    std::cin >> k;
    std::vector<int> first(2 * k), second(2 * k);
    for (int& x : first) std::cin >> x;
    for (int& x : second) std::cin >> x;

    std::vector<int> has_first(8 * k + 1), has_second(8 * k + 1);
    for (int num : first) has_first[num] = true;
    for (int num : second) has_second[num] = true;

    std::vector<int> choice(8 * k + 1);
    for (int i = 0; i <= 8 * k; ++i) {
        choice[i] = i;
    }
    std::shuffle(choice.begin(), choice.end(), g);

    for (int target : choice) {
        std::pair<int, int> first_pair = {-1, -1};
        std::pair<int, int> second_pair = {-1, -1};

        for (int num : first) if (num < target && target - num != num && has_first[target - num]) {
            first_pair = {num, target - num};
            break;
        }

        for (int num : second) if (num < target && target - num != num && has_second[target - num]) {
            second_pair = {num, target - num};
            break;
        }

        if (first_pair.first != -1 && second_pair.first != -1) {
            std::cout << first_pair.first << ' ' << first_pair.second << ' ' << second_pair.first << ' ' << second_pair.second;
            return 0;
        }
    }

    std::cout << -1;
}