#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#define int long long

int p = 31;
int mod = 1e9 + 9;
std::vector<int> powers(1e4 + 5, 1);

std::string decision(std::vector<std::string>& strs, std::vector<std::vector<int>>& hashes, int assumption) {
    std::pair<int, int> res_pos;
    std::unordered_set<int> cur_gen, next_gen;
    for (int k = 0; k < strs.size(); ++k) {
        next_gen.clear();

        for (int pos = 0; pos + assumption <= strs[k].size(); ++pos) {
            int comparison_hash = (hashes[k][pos + assumption] - hashes[k][pos] * powers[assumption]) % mod;
            if (comparison_hash < 0) comparison_hash += mod;

            if (cur_gen.empty() || cur_gen.contains(comparison_hash)) {
                next_gen.insert(comparison_hash);
                res_pos = {k, pos};
            }
        }

        std::swap(next_gen, cur_gen);
        if (cur_gen.empty()) break;
    }

    if (cur_gen.empty()) return "";
    return strs[res_pos.first].substr(res_pos.second, assumption);
}

signed main() {
    freopen("substr.in", "r", stdin);
    freopen("substr.out", "w", stdout);

    int k;
    std::cin >> k;
    std::vector<std::string> strings(k);
    int min_size = 1e9;
    for (int i = 0; i < k; ++i) {
        std::cin >> strings[i];
        min_size = std::min((int)strings[i].size(), min_size);
    }

    for (int i = 1; i < 1e4 + 5; ++i) {
        powers[i] = powers[i - 1] * p % mod;
    }

    std::vector<std::vector<int>> prefix_hashes(k);
    for (int i = 0; i < k; ++i) {
        prefix_hashes[i].resize(strings[i].size() + 1);
        for (int j = 0; j < strings[i].size(); ++j) {
            prefix_hashes[i][j + 1] = (p * prefix_hashes[i][j] + strings[i][j] - 'a' + 1) % mod;
        }
    }

    int left = 0;
    int right = min_size;
    std::string answer;
    while (left <= right) {
        int middle = (left + right) / 2;

        std::string tmp = decision(strings, prefix_hashes, middle);
        if (!tmp.empty()) {
            left = middle + 1;
            answer = tmp;
        }
        else {
            right = middle - 1;
        }
    }

    std::cout << answer;
}