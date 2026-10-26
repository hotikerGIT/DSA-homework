#include <iostream>
#include <vector>
#define int long long

struct Block {
    int size;
    std::vector<int> vec;
    int min;

    Block(int s, std::vector<int>& a, int left) : size(s) {
        vec.resize(size);
        min = 1e18;

        for (int i = 0; i < size; ++i) {
            vec[i] = a[left + i];
            min = std::min(min, vec[i]);
        }
    }
};

signed main() {
    const int block_size = 320;

    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    std::vector<Block> blocks;
    for (int i = 0; i < n; i += block_size) {
        Block b = Block(std::min(n - block_size, block_size), a, i);
        blocks.push_back(b);
    }

    int q;
    std::cin >> q;

    while (q--) {
        int com;
        std::cin >> com;

        if (com == 1) {
            int l, r, k;
            std::cin >> l >> r >> k;
            --l; --r;

            int left_block_index = l / block_size;
            int right_block_index = r / block_size;
            Block& left_block = blocks[left_block_index];
            Block& right_block = blocks[right_block_index];

            int ans = 1e18;

            for (int i = l; i <= std::min(r, left_block_index * block_size - 1); ++i) {
                ans = std::min(ans, a[i]);
            }

            if (left_block_index != right_block_index) {
                for (int i = right_block_index * block_size + 1; i <= r; ++i) {
                    ans = std::min(ans, a[i]);
                }
            }

            for (int i = left_block_index + 1; i < right_block_index; ++i) {
                ans = std::min(ans, blocks[i].min);
            }

            std::cout << ans << std::endl;
        }

        else {
            int x, d;

        }
    }
}