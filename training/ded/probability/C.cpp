#include <vector>
#include <iostream>
#include <string>
#include <iomanip>

int main() {
    std::string s;
    std::cin >> s;

    double sum = 0;
    std::vector<int> counter(26);

    for (char c : s) {
        counter[c - 'a']++;
    }

    for (char c : s) {
        sum += (double)counter[c - 'a'] / s.size();
    }

    std::cout << std::fixed << std::setprecision(9) << sum;
}