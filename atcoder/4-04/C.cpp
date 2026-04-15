#include <iostream>
#include <string>
#include <vector>
#include <set>

int main() {
    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> char_pos(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        char_pos[i] = {a, b};
    }

    int m;
    std::cin >> m;
    std::vector<std::string> strings(m);
    for (int i = 0; i < m; ++i) {
        std::cin >> strings[i];
    }

    std::vector<std::set<char>> possible(n);
    for (const auto& s : strings) {
        for (int j = 0; j < n; ++j) {
            if ((int)s.size() != char_pos[j].first) continue;
            int idx = char_pos[j].second - 1;
            if (idx < 0 || idx >= (int)s.size()) continue;
            possible[j].insert(s[idx]);
        }
    }

    for (const auto& s : strings) {
        bool flag = true;
        if ((int)s.size() != n) flag = false;
        else {
            for (int i = 0; i < n; ++i) {
                if (possible[i].find(s[i]) == possible[i].end()) {
                    flag = false;
                    break;
                }
            }
        }
        std::cout << (flag ? "Yes" : "No") << '\n';
    }
}