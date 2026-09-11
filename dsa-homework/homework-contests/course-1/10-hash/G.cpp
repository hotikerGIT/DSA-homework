#include <iostream>
#include <vector>
#include <string>

int main() {
    std::string s;
    std::cin >> s;

    int mod = 1e9 + 9;
    int prime = 31;

    std::vector<long long> prefix_hashes(s.size() + 1, 0);
    std::vector<long long> powers(s.size() + 1, 1);

    for (int i = 1; i <= s.size(); ++i) {
        powers[i] = powers[i - 1] * prime % mod;
    }

    for (int i = 0; i < s.size(); ++i) {
        prefix_hashes[i + 1] = (prefix_hashes[i] * prime + s[i] - 'a' + 1) % mod;
    }

    for (int i = s.size() - 1; i > 0; --i) {
        long long prefix_hash = prefix_hashes[i];

        long long suffix_hash = (prefix_hashes[s.size()] - prefix_hashes[s.size() - i] * powers[i]) % mod;
        if (suffix_hash < 0) suffix_hash += mod;

        if (prefix_hash != suffix_hash) continue;

        long long window_hash = prefix_hash;

        for (int j = 1; j + i < s.size(); ++j) {
            long long new_hash = (window_hash - (s[j - 1] - 'a' + 1) * powers[i - 1]) % mod;
            if (new_hash < 0) new_hash += mod;
            window_hash = (new_hash * prime + s[j + i - 1] - 'a' + 1) % mod;

            if (window_hash == prefix_hash) {
                std::cout << s.substr(0, i);
                return 0;
            }
        }
    }

    std::cout << "Just a legend" << std::endl;
}