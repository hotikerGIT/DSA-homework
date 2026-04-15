#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> names(n);
    for (int i = 0; i < n; ++i) std::cin >> names[i];

    std::unordered_map<std::string, std::unordered_set<std::string>> bad;
    for (int i = 0; i < m; ++i) {
        std::string name1, name2;
        std::cin >> name1 >> name2;
        bad[name1].insert(name2);
        bad[name2].insert(name1);
    }

    std::vector<std::string> ans;
    for (int mask = 0; mask < 1 << n; ++mask) {
        int i = mask;
        int index = -1;
        std::vector<std::string> pick;

        while (i > 0) {
            int bit = i & 1;
            i /= 2;
            index++;
            if (!bit) continue;

            const std::string& name = names[index];
            bool flag = true;

            for (auto& check : pick) {
                if (bad[check].contains(name)) {
                    flag = false;
                    break;
                }
            }

            if (flag) {
                pick.push_back(name);
            }

            else {
                break;
            }
        }

        if (pick.size() > ans.size()) {
            std::swap(pick, ans);
        }
    }

    std::sort(ans.begin(), ans.end());
    std::cout << ans.size() << '\n';

    for (auto& name : ans) {
        std::cout << name << '\n';
    }
}