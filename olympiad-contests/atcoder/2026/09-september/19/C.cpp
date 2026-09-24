#include <set>
#include <iostream>
#include <vector>

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::multiset<int, std::ranges::greater> check;
    check.insert(a[0]);
    check.insert(a[1]);

    for (int k = 2; k < n; ++k) {
        check.insert(a[k]);
        auto it = check.begin();
        std::advance(it, 2);

        std::cout << *it << '\n';
    }
}