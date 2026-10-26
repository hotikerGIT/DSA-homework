#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#define int long long

signed main() {
    freopen("basketball.in", "r", stdin);
    freopen("basketball.out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector<std::string> names(n);
    for (int i = 0; i < n; ++i) std::cin >> names[i];
    int m;
    std::cin >> m;
    int a = 0; int b = 0;
    std::unordered_map<std::string, int> score;
    int max_score = 0;

    for (int i = 0; i < m; ++i) {
        std::string s;
        std::cin >> s;
        int cur_a = 0; int cur_b = 0;

        int j = 0;
        while (s[j] != ':') {
            cur_a = 10 * cur_a + s[j] - '0';
            ++j;
        }

        ++j;
        while (j < s.size()) {
            cur_b = 10 * cur_b + s[j] - '0';
            ++j;
        }

        std::string name;
        std::cin >> name;
        score[name] += cur_b - b;
        score[name] += cur_a - a;

        max_score = std::max(max_score, score[name]);
        a = cur_a;
        b = cur_b;
    }

    for (auto& [name, sc] : score) {
        if (sc == max_score) {
            std::cout << name << ' ' << sc;
            break;
        }
    }
}