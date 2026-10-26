#include <iostream>
#include <vector>
#include <set>
#include <unordered_set>

struct Point {
    int x, y, idx;
};

int distance(Point& a, Point& b) {
    return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
}

int main() {
    freopen("problem.in", "r", stdin);
    freopen("problem.out", "w", stdout);
    int n;
    std::cin >> n;
    std::vector<Point> points(n);
    for (int i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        points[i] = Point(a, b, i);
    }

    int best = 1e9;
    for (int i = 0; i < n; ++i) {
        Point start = points[i];
        std::unordered_set<int> take = {i};
        int time = 0;

        for (int j = 0; j < n - 1; ++j) {
            int best_index = -1;
            int best_distance = 1e9;

            for (int k = 0; k < n; ++k) {
                if (take.contains(k)) continue;

                int dist = distance(start, points[k]);
                if (dist < best_distance) {
                    best_index = k;
                    best_distance = dist;
                }
            }

            take.insert(best_index);
            time += best_distance;
            start = points[best_index];
        }

        best = std::min(best, time);
    }

    std::cout << best;
}