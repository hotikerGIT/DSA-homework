#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

int main() {
    int n;
    std::cin >> n;

    std::unordered_map<std::string, int> log;
    std::vector<std::pair<std::string, int>> queries;
    queries.reserve(n);

    for (int i = 0; i < n; ++i) {
        std::string name;
        int score;
        std::cin >> name >> score;
        queries.emplace_back(name, score);

        log[name] += score;
    }

    int max = 0;
    for (auto& [name, score] : log) {
        max = std::max(max, score);
    }

    int best_move = 1e9;
    std::string winner;

    for (auto& [name, score] : log) {
        if (log[name] == max) {
            int best = 0;

            for (int i = 0; i < n; ++i) {
                if (queries[i].first == name) best += queries[i].second;

                if (best >= max) {
                    if (best_move > i) {
                        winner = name;
                        best_move = i;
                    }
                    break;
                }
            }
        }
    }
    std::cout << winner << std::endl;

    return 0;
}