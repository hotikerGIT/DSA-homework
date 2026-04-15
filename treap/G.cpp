#include <iostream>
#include <list>
#include <map>
const int BLOCK_SIZE = 450;
const int MIN_BLOCK_SIZE = 200;

struct Block {
    int size = 0;
    std::list<int> content;
    std::map<int, int> counter;

    Block() = default;

    void Insert(int pos, int element) {
        auto it = content.begin();
        std::advance(it, pos);
        content.insert(it, element);
        ++size;
        counter[element]++;
    }

    int Take(int pos) {
        auto it = content.begin();
        std::advance(it, pos);
        int ans = *it;
        content.erase(it);
        --size;
        counter[ans]--;
        return ans;
    }

    void PushBack(int element) {
        content.push_back(element);
        ++size;
        counter[element]++;
    }

    int getFullCount(int element) {
        return counter[element];
    }

    std::pair<int, int> getSplitCount(int pos, int element) {
        int left_count = 0;
        int right_count = 0;
        int i = 0;

        for (int val : content) {
            if (i <= pos) left_count += val == element;
            if (i >= pos) right_count += val == element;
            i++;
        }

        return {left_count, right_count};
    }

    int GetSize() const {
        return size;
    }
};

std::list<Block> composition;

void split(std::list<Block>::iterator it) {
    auto next_block_it = composition.insert(std::next(it), Block());

    int mid = it->size / 2;
    auto split_it = it->content.begin();
    std::advance(split_it, mid);

    next_block_it->content.splice(next_block_it->content.begin(),
                              it->content,
                              split_it, it->content.end());

    next_block_it->size = next_block_it->content.size();
    it->size = it->content.size();

    for (int val : next_block_it->content) {
        it->counter[val]--;
        next_block_it->counter[val]++;
    }
}

void merge(std::list<Block>::iterator it) {
    if (it != composition.begin()) {
        auto prev_it = std::prev(it);
        for (int val : it->content) {
            prev_it->counter[val]++;
        }
        prev_it->content.splice(prev_it->content.end(), it->content);
        prev_it->size = prev_it->content.size();

        composition.erase(it);
        return;
    }

    auto next_it = std::next(it);
    if (next_it != composition.end()) {
        for (int val : next_it->content) {
            it->counter[val]++;
        }
        it->content.splice(it->content.end(), next_it->content);
        it->size = it->content.size();

        composition.erase(next_it);
    }
}

void build(int n) {
    composition.emplace_back();

    for (int i = 0; i < n; ++i) {
        int num;
        std::cin >> num;

        auto last_block_it = std::prev(composition.end());
        last_block_it->PushBack(num);

        if (last_block_it->GetSize() == BLOCK_SIZE) composition.emplace_back();
    }
}

std::pair<std::list<Block>::iterator, int> findPosition(int index) {
    auto it = composition.begin();
    int passed = 0;

    while (it != composition.end()) {
        if (passed + it->GetSize() > index) {
            return {it, index - passed};
        }
        passed += it->GetSize();
        ++it;
    }
    return {composition.end(), 0};
}

void move(int l, int r) {
    auto [left_block, left_pos] = findPosition(l);
    auto [right_block, right_pos] = findPosition(r);

    int element = right_block->Take(right_pos);
    left_block->Insert(left_pos, element);

    if (left_block->GetSize() >= BLOCK_SIZE) {
        split(left_block);
    }
    if (right_block->GetSize() <= MIN_BLOCK_SIZE) {
        merge(right_block);
    }
}

int query(int l, int r, int k) {
    auto [left_block, left_pos] = findPosition(l);
    auto [right_block, right_pos] = findPosition(r);

    int ans = 0;

    if (left_block == right_block) {
        auto it = left_block->content.begin();
        std::advance(it, left_pos);
        for (int i = left_pos; i <= right_pos; ++i) {
            if (*it == k) ans++;
            ++it;
        }

    } else {
        ans = left_block->getSplitCount(left_pos, k).second;
        ans += right_block->getSplitCount(right_pos, k).first;
        ++left_block;
        while (left_block != right_block) {
            ans += left_block->getFullCount(k);
            ++left_block;
        }
    }

    return ans;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, q;
    std::cin >> n;
    build(n);
    std::cin >> q;
    int last_ans = 0;

    for (int i = 0; i < q; ++i) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int l, r;
            std::cin >> l >> r;

            int l_i = (last_ans + l - 1) % n;
            int r_i = (last_ans + r - 1) % n;

            move(std::min(l_i, r_i), std::max(l_i, r_i));
        }

        else {
            int l, r, k;
            std::cin >> l >> r >> k;

            int l_i = (last_ans + l - 1) % n;
            int r_i = (last_ans + r - 1) % n;
            int k_i = (last_ans + k - 1) % n + 1;

            last_ans = query(std::min(l_i, r_i), std::max(l_i, r_i), k_i);
            std::cout << last_ans << '\n';
        }
    }
}