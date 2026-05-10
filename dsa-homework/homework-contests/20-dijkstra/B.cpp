#include <iostream>
#include <vector>

struct Car {
    std::vector<std::vector<int>> dist;

    Car() = default;

    explicit Car(int n) {
        dist.resize(n, std::vector<int>(n));

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                std::cin >> dist[i][j];
            }
        }
    }

    void Floyd_Warshall() {
        for (int k = 0; k < dist.size(); ++k) {
            for (int i = 0; i < dist.size(); ++i) {
                for (int j = 0; j < dist.size(); ++j) {
                    dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m, r;
    std::cin >> n >> m >> r;

    std::vector<Car> cars(m);
    for (int i = 0; i < m; ++i) {
        cars[i] = Car(n);
        cars[i].Floyd_Warshall();
    }

    std::vector dist(n + 1, std::vector(n, std::vector<int>(n, 2e9)));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (auto& car : cars) {
                dist[0][i][j] = std::min(dist[0][i][j], car.dist[i][j]);
            }
        }
    }


    for (int p = 1; p < n + 1; ++p) {
        for (int u = 0; u < n; ++u) {
            for (int v = 0; v < n; ++v) {
                if (u == v) continue;
                for (int s = 0; s < n; ++s) {
                    dist[p][u][v] = std::min(dist[p][u][v], dist[0][u][s] + dist[p - 1][s][v]);
                }
            }
        }
    }

    for (int i = 0; i < r; ++i) {
        int s, t, k;
        std::cin >> s >> t >> k;
        k = std::min(k, n);
        std::cout << dist[k][s - 1][t - 1] << '\n';
    }
}