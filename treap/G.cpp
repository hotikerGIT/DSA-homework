#include <iostream>
#include <list>
#include <vector>
#include <deque>
const int BLOCK_SIZE = 300;
const int MAX_VAL = 100000;

struct Block {
    std::deque<int> content;
    std::vector<int> counter;

    Block() { counter.resize(MAX_VAL + 1, 0); }

    void Insert(int pos, int element) {
        auto it = content.begin() + pos;
        content.insert(it, element);
        counter[element]++;
    }

    int Take(int pos) {
        auto it = content.begin() + pos;
        int ans = content[pos];
        content.erase(it);
        counter[ans]--;
        return ans;
    }

    void PushBack(int element) {
        content.push_back(element);
        counter[element]++;
    }

    int TakeBack() {
        int ans = content.back();
        counter[ans]--;
        content.pop_back();
        return ans;
    }

    int getFullCount(int element) {
        return counter[element];
    }

    std::pair<int, int> getSplitCount(int pos, int element) {
        int left_count = 0;
        int right_count = 0;
        int i = 0;

        for (int val : content) {
            if (i <= pos) left_count += (val == element);
            if (i >= pos) right_count += (val == element);
            i++;
        }

        return {left_count, right_count};
    }

    int GetSize() const {
        return content.size();
    }
};

std::vector<Block> composition;

void build(const std::vector<int>& vec) {
    composition.clear();
    composition.emplace_back();

    for (auto num : vec) {
        auto last_block_it = std::prev(composition.end());
        last_block_it->PushBack(num);

        if (last_block_it->GetSize() == BLOCK_SIZE) {
            composition.emplace_back();
        }
    }
}

std::pair<int, int> findPosition(int index) {
    return {index / BLOCK_SIZE, index % BLOCK_SIZE};
}

void move(int l, int r) {
    auto [left_block, left_pos] = findPosition(l);
    auto [right_block, right_pos] = findPosition(r);


    int element = composition[right_block].Take(right_pos);
    composition[left_block].Insert(left_pos, element);
    while (true) {
        if (left_block == right_block) break;
        int last = composition[left_block].TakeBack();
        ++left_block;
        composition[left_block].Insert(0, last);
    }
}

int query(int l, int r, int k) {
    auto [left_block, left_pos] = findPosition(l);
    auto [right_block, right_pos] = findPosition(r);

    int ans = 0;

    if (left_block == right_block) {
        for (int i = left_pos; i <= right_pos; ++i) {
            ans += composition[left_block].content[i] == k;
        }

    } else {
        ans = composition[left_block].getSplitCount(left_pos, k).second;
        ans += composition[right_block].getSplitCount(right_pos, k).first;
        ++left_block;
        while (left_block != right_block) {
            ans += composition[left_block].getFullCount(k);
            ++left_block;
        }
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) std::cin >> a[i];

    build(a);

    std::cin >> q;
    int last_ans = 0;
    int move_counter = 0;

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l, r;
            std::cin >> l >> r;

            int l_i = (last_ans + l - 1) % n;
            int r_i = (last_ans + r - 1) % n;

            move(std::min(l_i, r_i), std::max(l_i, r_i));
            move_counter++;
        } else {
            int l, r, k;
            std::cin >> l >> r >> k;

            int l_i = (last_ans + l - 1) % n;
            int r_i = (last_ans + r - 1) % n;
            int k_i = (last_ans + k - 1) % n + 1;

            last_ans = query(std::min(l_i, r_i), std::max(l_i, r_i), k_i);
            std::cout << last_ans << '\n';
        }
    }

    return 0;
}