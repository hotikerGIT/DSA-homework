#include <iostream>
#include <vector>
#include <set>

int block_size = 800;

struct Block {
    std::multiset<int> content;

    void add_num(int new_num) {
        content.insert(new_num);
    }

    void change_num(int prev_num, int new_num) {
        content.erase(content.find(prev_num));
        add_num(new_num);
    }

    int get_size() const {
        return content.size();
    }
};

int main() {
    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    std::vector<Block> decompose;
    for (int i = 0; i < n; ++i) {
        if (decompose.empty() || decompose.back().get_size() == block_size) {
            decompose.emplace_back();
        }

        decompose.back().add_num(a[i]);
    }

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int ind, v;
            std::cin >> ind >> v;
            ind--;
            int old_ind = ind;

            for (auto& block : decompose) {
                if (ind < block.get_size()) {
                    block.change_num(a[old_ind], v);
                    break;
                }

                ind -= block.get_size();
            }

            a[old_ind] = v;

        } else {
            int l, r, s;
            std::cin >> l >> r >> s;
            l--; r--;

            int old_left = l; int old_right = r;
            int left_border = 0;
            int right_border = 0;

            int left_id = 0;
            for (int block_id = 0; block_id < decompose.size(); ++block_id) {
                auto& block = decompose[block_id];

                if (l < block.get_size()) {
                    left_id = block_id;
                    break;
                }

                l -= block.get_size();
                left_border += block.get_size();
                right_border += block.get_size();
            }
            left_border += decompose[left_id].get_size();

            int right_id = 0;
            for (int block_id = left_id; block_id < decompose.size(); ++block_id) {
                auto& block = decompose[block_id];

                if (r < block.get_size()) {
                    right_id = block_id;
                    break;
                }

                r -= block.get_size();
                right_border += block.get_size();
            }

            auto left_block = Block();
            for (int ind = old_left; ind < left_border; ++ind) {
                left_block.add_num(a[ind]);
            }

            auto right_block = Block();
            for (int ind = right_border; ind <= old_right; ++ind) {
                right_block.add_num(a[ind]);
            }

            std::vector<Block*> blocks;
            blocks.push_back(&left_block);

            if (left_id != right_id) {
                blocks.push_back(&right_block);
            }

            for (int id = left_id; id < right_id; ++id) {
                blocks.push_back(&decompose[id]);
            }

            int cur_remainder = s;
            int target_mod = 0;
            while (cur_remainder > target_mod) {
                for (auto& block : blocks) {
                    auto it = block->content.upper_bound(cur_remainder);
                    if (it != block->content.begin()) {
                        target_mod = std::max(target_mod, *std::prev(it));
                    }
                }

                if (target_mod) cur_remainder %= target_mod;
                else break;
                target_mod = 0;
            }

            std::cout << cur_remainder << '\n';
        }
    }
}