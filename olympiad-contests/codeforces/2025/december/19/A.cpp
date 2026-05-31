#include <iostream>
#include <unordered_set>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int l, a, b;
        std::cin >> l >> a >> b;
        int max_score = 0;
        std::unordered_set<int> visited;

        for (int i = 0; i < l; ++i) {
            int score = (a + b * i) % l;
            if (visited.contains(score)) break;
            visited.insert(score);
            max_score = std::max(max_score, score);
        }

        std::cout << max_score << std::endl;
    }
}