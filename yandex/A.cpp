#include <unordered_map>
#include <iostream>
#include <vector>
#include <set>
#include <string>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::unordered_map<char, std::set<std::pair<int, std::string>>> dict;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        dict[s[0]].insert({0, s});
    }

    for (int i = 0; i < m; ++i) {
        char c;
        std::cin >> c;
        auto res_it = dict[c].begin();
        auto [times, res] = *res_it;
        dict[c].erase(res_it);
        dict[c].insert({times + 1, res});
        std::cout << res << '\n';
    }
}