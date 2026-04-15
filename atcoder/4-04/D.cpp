#include <string>
#include <iostream>
#include <vector>
#include <deque>
#include <set>

int main() {
    std::string s, t;
    std::cin >> s >> t;

    std::deque<char> cur;
    std::set<char> bad(t.begin(), t.end());
    int l = 0, r = 0, t_r = 0;
    int ans = 0;
    while (r < s.size()) {
        while (r < s.size() && t_r != t.size()) {
            if (s[r] == t[t_r]) {
                t_r++;
            }

            if (bad.contains(s[r])) cur.push_back(s[r]);
            r++;
        }

        ans += r - l;

        bool flag = true;
        do {
            if (s[l] == t[0]) {
                while (cur[0] != t[0]) {
                    cur.pop_back();
                }
                flag = false;
            }

            if (bad.contains(s[l])) {
                cur.pop_back();
            }
            l++;
        } while (flag);
    }

    std::cout << ans;
}