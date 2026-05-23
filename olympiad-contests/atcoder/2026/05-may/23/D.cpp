#include <iostream>
#include <string>
#include <vector>
#include <map>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        std::string s;
        std::cin >> s;
        std::map<char, int> counter;
        int max = 0;
        for (auto c : s) {
            counter[c]++;
            max = std::max(max, counter[c]);
        }

        if (max > s.size() / 2) {
            std::cout << "No\n";
            continue;
        }

        std::string res;
        auto first_max_it = --counter.end();
        auto second_max_it = ----counter.end();

        while (first_max_it->second > 0) {
            res += first_max_it->first;
            res += second_max_it->first;

            first_max_it->second--;
            second_max_it->second--;

            if (first_max_it->second == 0) {
                --first_max_it;

                if (second_max_it == counter.begin()) {
                    if (second_max_it->second == 1) res += second_max_it->first;
                    break;
                }

                --second_max_it;
            }
        }

        std::cout << "Yes\n";
        std::cout << res << '\n';
    }
}