#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <queue>

std::vector<int> answer(const std::vector<int>& vec) {
    std::set<int> order;
    std::unordered_set<int> seen;
    std::unordered_map<int, int> counter_right;
    std::unordered_map<int, int> counter_queue;
    for (int num : vec) counter_right[num]++;
    std::vector<int> res;
    res.reserve(counter_right.size());

    std::queue<int> q;
    int right = 0;
    while (right < vec.size()) {
        int last_number;
        while (right < vec.size()) {
            auto current = vec[right];
            right++;

            if (seen.contains(current)) continue;

            q.push(current);
            order.insert(current);
            counter_right[current]--;
            counter_queue[current]++;

            if (!counter_right[current]) {
                last_number = current;
                break;
            }
        }

        while (!q.empty() && !seen.contains(last_number)) {
            if (res.size() % 2 == 0) {
                int window_max = *order.rbegin();

                if (seen.contains(window_max)) {
                    order.erase(window_max);
                    continue;
                }

                res.push_back(window_max);
                seen.insert(window_max);

                while (!q.empty() && q.front() != window_max) {
                    if (counter_queue[q.front()] == 1) order.erase(q.front());
                    counter_queue[q.front()]--;
                    q.pop();
                }

                while (!q.empty() && q.front() == window_max) {
                    if (counter_queue[q.front()] == 1) order.erase(q.front());
                    counter_queue[q.front()]--;
                    q.pop();
                }
            }

            else {
                int window_min = *order.begin();

                if (seen.contains(window_min)) {
                    order.erase(window_min);
                    continue;
                }
                res.push_back(window_min);
                seen.insert(window_min);

                while (!q.empty() && q.front() != window_min) {
                    if (counter_queue[q.front()] == 1) order.erase(q.front());
                    counter_queue[q.front()]--;
                    q.pop();
                }

                while (!q.empty() && q.front() == window_min) {
                    if (counter_queue[q.front()] == 1) order.erase(q.front());
                    counter_queue[q.front()]--;
                    q.pop();
                }
            }
        }
    }

    return res;
}

int main() {
    int t;
    std::cin >> t;

    while (t--) {
        int n;
        std::cin >> n;
        std::vector<int> a(n);
        for (int i = 0; i < n; ++i) std::cin >> a[i];
        auto ans = answer(a);

        std::cout << ans.size() << '\n';
        for (int num : ans) std::cout << num << ' ';
        std::cout << '\n';
    }
}