#include <iostream>
#include <vector>
#define int long long

struct Block {
    int size;
    std::vector<long long> content;
    long long sum;
    long long addition = 0;  // значение которое добавляется к каждому элементу блока

    Block(int size, std::vector<int>& vec, int left)
            : size(size)
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
    int block_size = 320;
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<Block> blocks;
    for (int i = 0; i < n; i += block_size) {
        int size = std::min(n - i, block_size);
        Block b = Block(size, a, i);
        blocks.push_back(b);
    }

    while (q--) {
        char command;
        std::cin >> command;

        int l, r, x;
        std::cin >> l >> r;
        --l; --r;

        int lb_index = l / block_size;
        int rb_index = r / block_size;

        Block& bl = blocks[lb_index];
        Block& br = blocks[rb_index];

        // правая граница в поиске будет равна r % bs если поиск внутри одного блока
        int right_in_block = (lb_index == rb_index) ? (r % block_size) : (bl.size - 1);

        x = 0;
        if (command == 'U') std::cin >> x;

        long long res = 0;

        // смотрим самый левый блок, попутно обновляя его значения
        for (int i = 0; i < bl.size; ++i) {
            bl.content[i] += bl.addition;

            if (i >= l % block_size && i <= right_in_block) {
                bl.content[i] += x;
                bl.sum += x;

                res += bl.content[i];
            }
        }

        bl.addition = 0;

        // то же самое и с правым
        if (lb_index != rb_index) {
            for (int i = 0; i < br.size; ++i) {
                br.content[i] += br.addition;

                if (i <= r % block_size) {
                    br.content[i] += x;
                    br.sum += x;

                    res += br.content[i];
                }
            }
        }

        br.addition = 0;

        for (int i = lb_index + 1; i < rb_index; ++i) {
            blocks[i].addition += x;
            blocks[i].sum += blocks[i].size * x;
            res += blocks[i].sum;
        }

        if (command == 'S') std::cout << res << std::endl;
    }
}
