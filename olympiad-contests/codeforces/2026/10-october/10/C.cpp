#include <iostream>
#include <vector>

int get_beauty(const std::vector<int>& a) {
    int n = a.size();
    std::vector<int> pref(n + 1);

    for (int i = 0; i < n; ++i) {
        pref[i + 1] = pref[i] ^ a[i];
    }

    int beauty = n;
    for (int l = 0; l < n; ++l) {
        for (int r = l; r < n; ++r) {
            beauty -= (pref[r + 1] ^ pref[l]) == 0;
        }
    }

    return beauty;
}

int main() {
//    std::vector<int> a(15);
//    for (int i = 0; i < a.size(); ++i) std::cin >> a[i];
//    std::cout << get_beauty(a) << std::endl;
    std::cout << (1 << 16);
    int difnum;
    std::cin >> difnum;
    for (int size = 3; size <= 7; ++size) {
        std::vector<int> a(size);
        int max = 0;
        int want = 1e9;

        auto backtrack = [&](int cur_ind, auto&& self) {
            if (cur_ind == a.size()) {
                int b = get_beauty(a);
                max = std::max(max, b);

                if (b == want) {
                    std::cout << "beauty " << b << ": ";
                    for (auto num : a) {
                        std::cout << num << ' ';
                    }
                    std::cout << std::endl;
                }
                return;
            }

            for (int i = 0; i <= difnum; ++i) {
                a[cur_ind] = i;
                self(cur_ind + 1, self);
            }
        };

        backtrack(0, backtrack);

        want = max;
        std::cout << "MAX FOR SIZE " << size << " IS " << want << std::endl;
        backtrack(0, backtrack);
        std::cout << max;
    }
}