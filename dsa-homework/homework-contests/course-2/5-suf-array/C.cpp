#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>

struct MinSparseTable {
    std::vector<std::vector<int>> table;

    explicit MinSparseTable(const std::vector<int>& data) {
        int n = data.size();
        int max_pow = std::floor(std::log2(n));
        table.resize(max_pow + 1);

        for (int num : data) table[0].push_back(num);

        for (int power = 1; power <= max_pow; ++power) {
            int half = (1 << (power - 1));

            for (int i = 0; i + half < table[power - 1].size(); ++i) {
                table[power].push_back(std::min(
                        table[power - 1][i],
                        table[power - 1][i + half]
                ));
            }
        }
    }

    int get_min(int l, int r) {
        int power = std::floor(std::log2(r - l + 1));
        int len = 1 << power;
        return std::min(
                table[power][l],
                table[power][r - len + 1]
        );
    }
};

struct SuffixArray {
    std::string s;
    int n;
    std::vector<int> array;
    std::vector<int> rev_array;
    std::vector<int> lcp_array;

    explicit SuffixArray(const std::string& s) : s(s), n(s.size()) {
        build_array();
        build_rev_array();
        build_lcp_array();
    }

    void build_array() {
        array.resize(n);
        for (int i = 0; i < n; ++i) array[i] = i;
        std::sort(array.begin(), array.end(), [&](int a, int b) {
            return s[a] < s[b];
        });

        std::vector<int> classes(n);
        for (int i = 1; i < n; ++i) {
            classes[array[i]] = classes[array[i - 1]]
                                + (s[array[i]] != s[array[i - 1]]);
        }

        for (int c = 1; c < n; c <<= 1) {
            std::sort(array.begin(), array.end(), [&](int a, int b) {
                if (classes[a] != classes[b]) return classes[a] < classes[b];
                int ca = a + c < n ? classes[a + c] : -1;
                int cb = b + c < n ? classes[b + c] : - 1;
                return ca < cb;
            });

            std::vector<int> new_classes(n);
            for (int i = 1; i < n; ++i) {
                int a = array[i];
                int b = array[i - 1];
                int ca = a + c < n ? classes[a + c] : -1;
                int cb = b + c < n ? classes[b + c] : -1;
                int same = classes[a] == classes[b] && ca == cb;
                new_classes[a] = new_classes[b] + (1 - same);
            }

            std::swap(classes, new_classes);
        }
    }

    void build_rev_array() {
        rev_array.resize(n);
        for (int i = 0; i < n; ++i) {
            rev_array[array[i]] = i;
        }
    }

    void build_lcp_array() {
        lcp_array.resize(n - 1);
        int cnt = 0;

        for (int i = 0; i < n; ++i) {
            if (rev_array[i] == n - 1) continue;

            int next = array[rev_array[i] + 1];
            while (
                    cnt < std::min(n - i, n - next)
                    && s[i + cnt] == s[next + cnt]
                    ) ++cnt;

            lcp_array[rev_array[i]] = cnt;
            cnt = std::max(0, cnt - 1);
        }
    }
};

int main() {
    std::freopen("substrcmp.in", "r", stdin);
    std::freopen("substrcmp.out", "w", stdout);

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::string s;
    std::cin >> s;
    auto array = SuffixArray(s);
    auto table = MinSparseTable(array.lcp_array);

    int m;
    std::cin >> m;
    for (int i = 0; i < m; ++i) {
        int a, b, c, d;
        std::cin >> a >> b >> c >> d;
        a--; b--; c--; d--;

        if (b - a != d - c) {
            std::cout << "No\n";
            continue;
        }

        if (a == c) {
            if (b != d) {
                std::cout << "No\n";
            } else {
                std::cout << "Yes\n";
            }

            continue;
        }

        int l = array.rev_array[a];
        int r = array.rev_array[c];
        if (r < l) std::swap(l, r);

        int lcp = table.get_min(l, r - 1);

        if (lcp < b - a + 1) {
            std::cout << "No\n";
        } else {
            std::cout << "Yes\n";
        }
    }
}