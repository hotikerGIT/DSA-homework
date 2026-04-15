#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

struct MinMax {
    int value = 0, max = 0, min = 1e9;
};

class MinMaxQueue {
private:
    std::vector<MinMax> add_stack;
    std::vector<MinMax> remove_stack;

    void transfer() {
        if (!remove_stack.empty()) return;

        while (!add_stack.empty()) {
            MinMax elem = add_stack.back();
            add_stack.pop_back();

            if (remove_stack.empty()) remove_stack.push_back({elem.value, elem.value, elem.value});
            else {
                remove_stack.push_back({
                    elem.value,
                    std::max(elem.value, remove_stack.back().max),
                    std::min(elem.value, remove_stack.back().min)
                });
            }
        }
    }

public:
    void push(int value) {
        if (add_stack.empty()) add_stack.push_back({value, value, value});
        else {
            add_stack.push_back({
                value,
                std::max(value, add_stack.back().max),
                std::min(value, add_stack.back().min)
            });
        }
    }

    void pop() {
        transfer();
        if (!remove_stack.empty()) {
            remove_stack.pop_back();
        }
    }

    MinMax front() {
        transfer();
        return remove_stack.back();
    }

    bool empty() const {
        return add_stack.empty() && remove_stack.empty();
    }
};

std::vector<int> answer(const std::vector<int>& vec) {
    std::unordered_set<int> seen;
    std::unordered_map<int, int> counter;
    for (int num : vec) counter[num]++;
    std::vector<int> res;
    res.reserve(counter.size());

    MinMaxQueue q;
    int right = 0;
    while (right < vec.size()) {
        while (right < vec.size()) {
            auto current = vec[right];
            right++;

            if (seen.contains(current)) continue;

            q.push(current);
            counter[current]--;

            if (!counter[current]) break;
        }

        while (!q.empty()) {
            auto tmp = q.front();

            if (res.size() % 2 == 0) {
                if (seen.contains(tmp.max)) {
                    q.pop();
                    continue;
                }
                res.push_back(tmp.max);
                seen.insert(tmp.max);

                while (!q.empty() && q.front().value != tmp.max) q.pop();
                while (!q.empty() && q.front().value == tmp.max) q.pop();
            }

            else {
                if (seen.contains(tmp.min)) {
                    q.pop();
                    continue;
                }
                res.push_back(tmp.min);
                seen.insert(tmp.min);

                while (!q.empty() && q.front().value != tmp.min) q.pop();
                while (!q.empty() && q.front().value == tmp.min) q.pop();
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