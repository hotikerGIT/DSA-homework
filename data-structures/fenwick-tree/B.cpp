#include <iostream>
#include <vector>

class FenvickTree {
private:
    int n;
    std::vector<std::vector<std::vector<int>>> tree;

    int get(int x, int y, int z) {
        int res = 0;

        while (x >= 0) {
            int tmp_y = y;

            while (tmp_y >= 0) {
                int tmp_z = z;

                while (tmp_z >= 0) {
                    res += tree[x][tmp_y][tmp_z];
                    tmp_z = (tmp_z & (tmp_z + 1)) - 1;
                }

                tmp_y = (tmp_y & (tmp_y + 1)) - 1;
            }

            x = (x & (x + 1)) - 1;
        }

        return res;
    }

    void update(int x, int y, int z, int k) {
        while (x < n) {
            int tmp_y = y;
            while (tmp_y < n) {
                int tmp_z = z;
                while (tmp_z < n) {
                    tree[x][tmp_y][tmp_z] += k;
                    tmp_z = tmp_z | (tmp_z + 1);
                }

                tmp_y = tmp_y | (tmp_y + 1);
            }

            x = x | (x + 1);
        }
    }

public:
    FenvickTree(int m) : n(m), tree(n, std::vector(n, std::vector(n, 0))) {}

    int query(int x1, int y1, int z1, int x2, int y2, int z2) {
        x1--; y1--; z1--;
        int s222 = get(x2, y2, z2);
        int s122 = get(x1, y2, z2) + get(x2, y1, z2) + get(x2, y2, z1);
        int s112 = get(x1, y1, z2) + get(x1, y2, z1) + get(x2, y1, z1);
        int s111 = get(x1, y1, z1);
        return s222 - s122 + s112 - s111;
    }

    void set(int x, int y, int z, int k) {
        update(x, y, z, k);
    }
};

int main() {
    freopen("stars.in", "r", stdin);
    freopen("stars.out", "w", stdout);

    int n;
    std::cin >> n;
    int x1, y1, z1, x2, y2, z2, k;
    FenvickTree FT(n);

    int type = 0;
    while (type != 3) {
        std::cin >> type;

        if (type == 1) {
            std::cin >> x1 >> y1 >> z1 >> k;
            FT.set(x1, y1, z1, k);
        }

        else if (type == 2) {
            std::cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
            std::cout << FT.query(x1, y1, z1, x2, y2, z2) << '\n';
        }
    }
}