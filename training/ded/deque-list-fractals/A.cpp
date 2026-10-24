#include <iostream>
#include <list>
#include <string>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, p;
    std::cin >> n >> p;
    std::list<int> a;

    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;
        a.push_back(num);
    }

    int cur = 1;
    auto it = a.begin();
    while (cur != p) {
        ++it;
        ++cur;
    }

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        std::string com;
        std::cin >> com;

        if (com == "print") {
            std::cout << *it << std::endl;
        } else if (com == "moveLeft") {
            if (it != a.begin()) --it;
        } else if (com == "moveRight") {
            ++it;
            if (it == a.end()) --it;
        } else if (com == "insertLeft") {
            int num;
            std::cin >> num;
            a.insert(it, num);
        } else {
            int num;
            std::cin >> num;
            a.insert(std::next(it), num);
        }
    }
}