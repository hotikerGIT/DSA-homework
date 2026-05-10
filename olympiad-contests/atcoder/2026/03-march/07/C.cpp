#include <iostream>
#include <vector>
#include <set>

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::multiset<int> query;
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
        query.insert(a[i]);
    }

    for (int i = 0; i < q; ++i) {
        int k;
        std::cin >> k;
        std::vector<int> removed;

        for (int j = 0; j < k; ++j) {
            int ind;
            std::cin >> ind;
            query.erase(query.find(a[ind - 1]));
            removed.push_back(a[ind - 1]);
        }

        std::cout << *query.begin() << '\n';

        for (int num : removed) {
            query.insert(num);
        }
    }
}