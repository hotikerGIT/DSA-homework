#include <string>
#include <iostream>
#include <vector>
#include <unordered_map>

int main() {
    int n, m;
    std::cin >> n >> m;
    std::vector<std::string> strings_vertical(n);
    std::vector<std::string> strings_horizontal(m);
    for (int i = 0; i < n; ++i) std::cin >> strings_vertical[i];
    for (int i = 0; i < m; ++i) std::cin >> strings_horizontal[i];
    std::vector<std::string_view> strings;
    strings.reserve(n * n);
    int mod = 1e9 + 9;
    int p = 4e6 + 9;
    std::vector<long long> powers(m + 1, 1);
    for (int power = 1; power <= m; ++power) powers[power] = (powers[power - 1] * p) % mod;

    for (int i = 0; i < n; ++i) strings.push_back(std::string_view(strings_vertical[i]));
    for (int i = 0; i < m; ++i) {
        for (int pos = 0; pos + m <= n; ++pos) {
            strings.push_back(std::string_view(strings_horizontal[i]).substr(pos, m));
        }
    }
    std::sort(strings.begin(), strings.end());
    // for (auto& str : strings) std::cout << str << std::endl;

    // в качестве хешей для строчек будем использовать их лексикографический порядок,
    // а для хеширования матрицы МхМ будем использовать хеши строк
    // причем хеши строк будут в худшем случае [1, n^2]
    int count_different = 1;
    std::unordered_map<std::string_view, int> hashes;
    for (auto& string : strings) {
        if (hashes.contains(string)) continue;
        hashes[string] = count_different;
        count_different++;
    }

    std::vector<long long> hashes_by_pos_vertical(n);
    std::vector<long long> hashes_by_pos_horizontal(n);

    for (int pos = 0; pos + m <= n; ++pos) {
        long long vertical_hash = 0;
        for (int row = 0; row < m; ++row) vertical_hash = (vertical_hash * p + hashes[std::string_view(strings_vertical[pos + row])]) % mod;

        hashes_by_pos_vertical[pos] = vertical_hash;
    }

    for (int pos = 0; pos + m <= n; ++pos) {
        long long horizontal_hash = 0;
        for (int row = 0; row < m; ++row) horizontal_hash = (horizontal_hash * p + hashes[std::string_view(strings_horizontal[row]).substr(pos, m)]) % mod;

        hashes_by_pos_horizontal[pos] = horizontal_hash;
    }

    for (int hpos = 0; hpos + m <= n; ++hpos) {
        for (int vpos = 0; vpos + m <= n; ++vpos) {
            if (hashes_by_pos_vertical[vpos] == hashes_by_pos_horizontal[hpos]) {
                std::cout << vpos + 1 << ' ' << hpos + 1;
                return 0;
            }
        }
    }
}