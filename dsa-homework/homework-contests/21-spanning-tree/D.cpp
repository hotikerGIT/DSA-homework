#include <vector>
#include <iostream>
#include <cmath>
#include <iomanip>

struct Edge {
    int from, to;
    double weight;
};

int main() {
    freopen("unionday.in", "r", stdin);
    freopen("unionday.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; ++i) {
        int x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    auto get_weight = [&](int p1, int p2) {
        auto& v1 = points[p1];
        auto& v2 = points[p2];

        return sqrt(
            (v1.first - v2.first) * (v1.first - v2.first) +
            (v1.second - v2.second) * (v1.second - v2.second)
            );
    };

    // для каждой вершины храним лучшее ребро из уже посещенных
    std::vector<double> best_edges(n, 2e9);
    best_edges[0] = 0;
    int best_choice = 0;
    int last_choice = 0;
    double ans = 0;
    std::vector<int> visited(n);

    for (int i = 0; i < n; ++i) {
        visited[best_choice] = 1;
        ans += best_edges[best_choice];

        last_choice = best_choice;
        best_choice = -1;

        double best_weight = 2e9;
        for (int next  = 1; next < n; ++next) {
            if (visited[next]) continue;

            double new_weight = get_weight(last_choice, next);
            if (new_weight < best_edges[next]) {
                best_edges[next] = new_weight;
            }
            if (best_edges[next] < best_weight) {
                best_weight = best_edges[next];
                best_choice = next;
            }
        }
    }

    std::cout << std::fixed << std::setprecision(6) << ans;
}