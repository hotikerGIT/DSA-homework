#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

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
    std::freopen("sufflcp.in", "r", stdin);
    std::freopen("sufflcp.out", "w", stdout);

    int n;
    std::string s;
    std::cin >> n >> s;
    std::vector<int> _(n);
    for (int& num : _) std::cin >> num;

    auto array = SuffixArray(s);
    for (int num : array.lcp_array) std::cout << num << ' ';
}