#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

bool cmp(std::string& a, std::string& b) {
    return a.size() < b.size();
}

int main() {
    int k;
    std::cin >> k;

    int p = 31;
    int mod = 1e9 + 9;

    std::vector<std::string> strings(k);
    std::vector<std::vector<long long>> prefix_hashes(k);
    std::vector<long long> powers(1e4 + 3, 1);
    for (int i = 1; i < powers.size(); ++i) powers[i] = powers[i - 1] * p % mod;

    for (int i = 0; i < k; ++i) std::cin >> strings[i];
    std::sort(strings.begin(), strings.end(), cmp);
    for (int i = 0; i < k; ++i) {
        std::string& s = strings[i];
        prefix_hashes[i].resize(s.size() + 1);

        for (int j = 0; j < s.size(); ++j) {
            prefix_hashes[i][j + 1] = (prefix_hashes[i][j] * p + s[j] - 'a' + 1) % mod;
        }
    }

    std::unordered_set<long long> hashes_of_common_substrings;
    std::unordered_set<long long> next_gen;
    int max_len = strings[0].size();
    std::string candidate;

    for (int i = 0; i < k; ++i) {
        std::string& s = strings[i];
        next_gen.clear();
        int max_len_on_iter = -1;

        for (int len = max_len; len > 0; --len) {
            for (int pos = 0; pos + len <= s.size(); ++pos) {
                long long hash = (prefix_hashes[i][pos + len] - prefix_hashes[i][pos] * powers[len]) % mod;
                if (hash < mod) hash += mod;

                if (i == 0 || hashes_of_common_substrings.contains(hash)) {
                    next_gen.insert(hash);
                    if (max_len_on_iter == -1) {
                        max_len_on_iter = len;
                        candidate = s.substr(pos, len);
                    }
                }
            }
        }

        std::swap(next_gen, hashes_of_common_substrings);
        max_len = max_len_on_iter;
    }

    std::cout << candidate << std::endl;
}