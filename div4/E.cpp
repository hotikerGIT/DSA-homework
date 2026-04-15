#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <queue>
#include <utility>

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n, k, x;
        std::cin >> n >> k >> x;
        std::vector<int> a(n);
        for (int i = 0; i < n; i++) std::cin >> a[i];

        // Добавляем граничные точки
        std::vector<int> points = a;
        points.push_back(0);
        points.push_back(x);

        std::sort(points.begin(), points.end());

        // Создаем интервалы между точками
        std::vector<std::pair<int, int>> intervals;
        for (int i = 1; i < points.size(); i++) {
            if (points[i-1] < points[i]) {
                intervals.emplace_back(points[i-1], points[i]);
            }
        }

        // Приоритетная очередь для хранения интервалов по их размеру
        // Храним: (-размер, левая_граница, правая_граница)
        std::priority_queue<std::tuple<int, int, int>> pq;

        for (const auto& interval : intervals) {
            int size = interval.second - interval.first;
            if (size > 0) {
                pq.emplace(size, interval.first, interval.second);
            }
        }

        std::vector<int> answer;
        answer.reserve(k);

        // Добавляем k точек
        for (int i = 0; i < k && !pq.empty(); i++) {
            auto [size, left, right] = pq.top();
            pq.pop();

            int mid = left + (right - left) / 2;
            answer.push_back(mid);

            // Разделяем интервал на две части
            if (mid - left > 0) {
                pq.emplace(mid - left, left, mid);
            }
            if (right - mid > 0) {
                pq.emplace(right - mid, mid, right);
            }
        }

        // Если нужно больше точек, чем доступных интервалов
        while (answer.size() < k) {
            answer.push_back(0); // или любое другое значение по умолчанию
        }

        // Выводим минимальное расстояние
        int min_distance = pq.empty() ? 0 : std::get<0>(pq.top());
        std::cout << min_distance << '\n';

        for (int num : answer) {
            std::cout << num << " ";
        }
        std::cout << '\n';
    }

    return 0;
}