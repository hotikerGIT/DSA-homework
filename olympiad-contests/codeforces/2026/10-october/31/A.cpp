#include <iostream>
#include <string>
#include <vector>

void solve() {
    int n, m;
    std::cin >> n >> m;
    std::string p, q;
    std::cin >> p >> q;
    std::vector<int> up(26), down(26);

    for (int i = 0; i < n; ++i) up[p[i] - 'a']++;
    for (int i = 0; i < m; ++i) down[q[i] - 'a']++;

    bool flag = true;
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + (char)i;

        if (c == 's' || c == 'i'|| c == 'x') {
            if (down[i] != up[i] - 1) {
                flag = false;
                break;
            }

        } else if (down[i] != up[i]) {
            flag = false;
            break;
        }
    }

    std::cout << (flag ? "YES" : "NO") << std::endl;
}

int main() {
    int t;
    std::cin >> t;
    while (t--) solve();
}