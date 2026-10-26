#include <iostream>
#include <vector>

int check(const std::vector<int>& order, std::vector<int> a) {
    std::vector<int> count(5);
    for (int i = 0; i < a.size(); ++i) count[a[i]]++;

    for (int type : order) {

    }
}


int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);

    for (int i = 0; i < n; ++i) std::cin >> a[i];
}