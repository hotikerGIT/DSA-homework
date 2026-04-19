#include <string>
#include <vector>
#include <iostream>
#include <map>

class dsu {
private:
    std::vector<int> parent;
    std::vector<std::string> roots;
    std::vector<int> rang;

public:
    dsu(int size) {
        parent.resize(size + 1);
        for (int i = 1; i <= size; ++i) {
            parent[i] = i;
        }
        rang.resize(size + 1, 1);
        roots.resize(size + 1, "0");
    }

    int get(int x) {
        if (parent[x] != x) {
            parent[x] = get(parent[x]);
        }
        return parent[x];
    }

    std::string get_root(int x) {
        return roots[get(x)];
    }

    bool set(int eq, std::string& val) {
        int p = get(eq);
        if (roots[p] != "0") return false;
        roots[p] = val;
        return true;
    }

    void unity(int x, int y) {
        x = get(x);
        y = get(y);

        if (x == y) return;
        if (rang[x] == rang[y]) rang[x]++;
        if (rang[x] < rang[y]) {
            parent[x] = y;
        } else {
            parent[y] = x;
        }
    }
};

bool is_digit(std::string& s) {
    for (auto c : s) {
        if (c < '0' || c > '9') return false;
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<std::string> first(n), second(n);
    for (int i = 0; i < n; ++i) std::cin >> first[i];
    for (int i = 0; i < n; ++i) std::cin >> second[i];

    std::map<std::string, int> dict;
    int cnt = 0;
    for (auto s : first) {
        if (is_digit(s)) continue;
        auto it = dict.find(s);

        if (it != dict.end()) continue;
        cnt++;
        dict[s] = cnt;
    }
    for (auto s : second) {
        if (is_digit(s)) continue;
        auto it = dict.find(s);

        if (it != dict.end()) continue;
        cnt++;
        dict[s] = cnt;
    }

    dsu d(cnt);
    for (int i = 0; i < n; ++i) {
        if (is_digit(first[i]) || is_digit(second[i])) continue;
        d.unity(dict[first[i]], dict[second[i]]);
    }
    for (int i = 0; i < n; ++i) {
        auto fs = first[i];
        auto ss = second[i];
        bool first_flag = is_digit(fs);
        bool second_flag = is_digit(ss);

        if (!first_flag && !second_flag) continue;
        if (first_flag && second_flag) {
            if (fs != ss) {
                std::cout << "NO";
                return 0;
            }

            continue;
        }
        if (first_flag) {
            auto root = d.get_root(dict[ss]);

            if (root == "0") {
                d.set(dict[ss], fs);
            } else {
                if (root != fs) {
                    std::cout << "NO";
                    return 0;
                }
            }

            continue;
        }

        auto root = d.get_root(dict[fs]);

        if (root == "0") {
            d.set(dict[fs], ss);
        } else {
            if (root != ss) {
                std::cout << "NO";
                return 0;
            }
        }
    }

    std::cout << "YES";
}