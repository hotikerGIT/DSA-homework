#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    freopen("kings.in", "r", stdin);
    freopen("kings.out", "w", stdout);
    int n, m, k, a, b, c;
    std::cin >> n >> m >> k >> a >> b >> c;
    std::vector<std::pair<int, std::string>> armies;
    armies.push_back({n * a, "Joffrey"});
    armies.push_back({m * b, "Robb"});
    armies.push_back({k * c, "Stannis"});

    std::sort(armies.begin(), armies.end());
    std::vector<std::string> out;
    for (auto& [val, name] : armies) {
        if (val == armies[2].first) {
            out.push_back(name);
        }
    }

    std::sort(out.begin(), out.end());
    for (auto& name : out) {
        std::cout << name << ' ';
    }
}