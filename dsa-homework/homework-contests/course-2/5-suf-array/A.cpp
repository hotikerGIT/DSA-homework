#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

struct SuffixArray {
    std::string s;
    int n;
    std::vector<int> array;

    explicit SuffixArray(const std::string& s) : s(s), n(s.size()) {
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
};

int main() {
    std::freopen("suffarray.in", "r", stdin);
    std::freopen("suffarray.out", "w", stdout);

    std::string s;
    std::getline(std::cin, s);
    auto array = SuffixArray(s);

    for (int num : array.array) {
        std::cout << num + 1 << ' ';
    }
}