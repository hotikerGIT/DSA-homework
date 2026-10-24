#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    std::string s;
    std::cin >> s;

    std::string res(s.size(), 'a');

    int half = s.size() / 2;
    int ll = 0;
    int lr = half - 1;
    int rl = half;
    int rr = s.size() - 1;

    while (ll <= lr) {
        std::unordered_map<char, int> counter;
        counter[s[ll]]++;
        counter[s[lr]]++;
        counter[s[rl]]++;
        counter[s[rr]]++;

        int best = 0;
        char c = 'a';

        for (auto& [key, value] : counter) {
            if (value > best) {
                best = value;
                c = key;
            }
        }

        res[ll] = c;
        res[lr] = c;
        res[rl] = c;
        res[rr] = c;

        ll++;
        rl++;
        lr--;
        rr--;
    }

    std::cout << res << std::endl;
}