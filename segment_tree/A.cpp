#include <iostream>
#include <vector>
#define int long long

struct Block {
    int size;
    std::vector<long long> content;
    long long sum;

    Block(int size, std::vector<int>& vec, int left): size(size)
    {
        content.resize(size);
        sum = 0;

        for (int i = 0; i < size; ++i) {
            content[i] = vec[i + left];
            sum += content[i];
        }
    }
};

signed main() {
    freopen("sum.in", "r", stdin);
    freopen("sum.out", "w", stdout);

    int block_size = 320;
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n, 0);

    std::vector<Block> blocks;
    for (int i = 0; i < n; i += block_size) {
        int size = std::min(n - i, block_size);
        Block b = Block(size, a, i);
        blocks.push_back(b);
    }

    while (q--) {
        char command;
        std::cin >> command;

        int first, second;
        std::cin >> first >> second;
        if (command == 'Q') {
            int l = --first;
            int r = --second;

            int lb_index = l / block_size;
            int rb_index = r / block_size;

            Block& bl = blocks[lb_index];
            Block& br = blocks[rb_index];

            // правая граница в поиске будет равна r % bs если поиск внутри одного блока
            int right_in_block = (lb_index == rb_index) ? (r % block_size) : (bl.size - 1);

            long long res = 0;

            // смотрим самый левый блок, попутно обновляя его значения
            for (int i = l % block_size; i <= right_in_block; ++i) {
                res += bl.content[i];
            }

            // то же самое и с правым
            if (lb_index != rb_index) {
                for (int i = 0; i <= r % block_size; ++i) {
                    res += br.content[i];
                }
            }

            for (int i = lb_index + 1; i < rb_index; ++i) {
                res += blocks[i].sum;
            }

            std::cout << res << std::endl;
        }

        else {
            int p = --first;
            int x = second;

            Block& block = blocks[p / block_size];
            int delta = x - block.content[p % block_size];

            block.content[p % block_size] = x;
            block.sum += delta;
        }
    }
}