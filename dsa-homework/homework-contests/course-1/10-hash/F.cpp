#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>

int main() {
    std::string s, begin, end;
    std::cin >> s >> begin >> end;
    std::vector<int> starting(s.size());
    std::vector<int> ending(s.size());

    if (begin.size() > s.size() || end.size() > s.size()) {
        std::cout << 0;
        return 0;
    }

    for (int i = 0; i <= s.size() - begin.size(); ++i) {
        if (s.substr(i, begin.size()) == begin) starting[i] = 1;
    }

    for (int i = end.size() - 1; i < s.size(); ++i) {
        if (s.substr(i - end.size() + 1, end.size()) == end) ending[i] = 1;
    }

    int p = 31;
    int mod1 = 1e9 + 9;
    int mod2 = 1e9 + 7;
    std::unordered_set<long long> check;
    for (int i = 0; i < s.size(); ++i) {
        if (!starting[i]) continue;

        long long hash1 = 0;
        long long hash2 = 0;

        for (int j = i; j < s.size(); ++j) {
            hash1 = hash1 * p + s[j] - 'a' + 1;
            hash2 = hash2 * p + s[j] - 'a' + 1;
            hash1 %= mod1;
            hash2 %= mod2;

            long long combined_hash = (hash1 << 32) ^ hash2;

            if (j - i + 1 >= std::max(begin.size(), end.size()) && ending[j]) {
                check.insert(combined_hash);
            }
        }
    }

    std::cout << check.size() << std::endl;
}