#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#define int long long

int p1 = 31;
int p2 = 37;
int mod1 = 1e9 + 9;
int mod2 = 1e9 + 7;
std::vector<int> powers1;
std::vector<int> powers2;

std::pair<int, int> compute_hash(const std::string& s) {
    int h1 = 0, h2 = 0;
    for (char c : s) {
        int val = c - 'a' + 1;
        h1 = (h1 * p1 + val) % mod1;
        h2 = (h2 * p2 + val) % mod2;
    }
    return {h1, h2};
}

signed main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::unordered_set<int>> memory1(7e5);
    std::vector<std::unordered_set<int>> memory2(7e5);
    for (int i = 0; i < n; ++i) {
        std::string tmp;
        std::cin >> tmp;
        auto hashes = compute_hash(tmp);
        memory1[tmp.size()].insert(hashes.first);
        memory2[tmp.size()].insert(hashes.second);
    }
    powers1.resize(7e5, 1);
    powers2.resize(7e5, 1);
    for (int i = 1; i < 7e5; ++i) {
        powers1[i] = (powers1[i - 1] * p1) % mod1;
        powers2[i] = (powers2[i - 1] * p2) % mod2;
    }

    for (int i = 0; i < m; ++i) {
        std::string s;
        std::cin >> s;
        int size = s.size();
        auto hashes = compute_hash(s);

        bool flag = false;
        for (int j = 0; j < size && !flag; ++j) {
            for (char c = 'a'; c <= 'c'; ++c) {
                if (s[j] == c) continue;
                int tmp_hash1 = hashes.first + (c - s[j]) * powers1[size - j - 1];
                tmp_hash1 %= mod1;
                if (tmp_hash1 < 0) tmp_hash1 += mod1;
                int tmp_hash2 = hashes.second + (c - s[j]) * powers2[size - j - 1];
                tmp_hash2 %= mod2;
                if (tmp_hash2 < 0) tmp_hash2 += mod2;

                if (memory1[size].contains(tmp_hash1) && memory2[size].contains(tmp_hash2)) flag = true;
            }
        }

        if (flag) std::cout << "YES\n";
        else std::cout << "NO\n";
    }
}