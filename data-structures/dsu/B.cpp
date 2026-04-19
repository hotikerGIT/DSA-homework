#include <vector>
#include <iostream>
#include <string>
#include <map>

class dsu {
    std::vector<int> parent;
    std::vector<int> prev_row;
    int comps = 0;

    int find(int x) {
        return parent[x] == x ? x : parent[x] = find(parent[x]);
    }

    void unite(int a, int b) {
        a = find(a); b = find(b);
        if (a != b) {
            parent[b] = a;
            comps--;
        }
    }

public:
    void add_row(const std::string& row) {
        int cols = row.size() * 4;
        std::vector<int> cur(cols, -1);

        for (int i = 0; i < row.size(); ++i) {
            char c = row[i];
            int num = (c >= '0' && c <= '9') ? c - '0' : c - 'A' + 10;

            for (int j = 0; j < 4; ++j) {
                int bit = (num >> (3 - j)) & 1;
                int index = i * 4 + j;
                if (!bit) continue;

                int id = parent.size();
                parent.push_back(id);
                cur[index] = id;
                comps++;

                if (index > 0 && cur[index - 1] != -1) unite(id, cur[index - 1]);
                if (!prev_row.empty() && prev_row[index] != -1) unite(id, prev_row[index]);

                cur[index] = find(id);
            }
        }


        std::vector<int> new_parent;
        std::vector<int> remap(parent.size(), -1);
        int new_id = 0;

        for (int i = 0; i < cols; ++i) {
            if (cur[i] != -1) {
                int root = find(cur[i]);
                if (remap[root] == -1) {
                    remap[root] = new_id++;
                    new_parent.push_back(new_parent.size());
                }
                cur[i] = remap[root];
            }
        }

        parent = std::move(new_parent);
        std::swap(prev_row, cur);
    }

    int total_components() const { return comps; }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, m;
    std::cin >> n >> m;
    dsu d;
    for (int i = 0; i < n; ++i) {
        std::string s;
        std::cin >> s;
        d.add_row(s);
    }
    std::cout << d.total_components();
}
