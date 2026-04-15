#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define int long long

std::vector<int> primes;
std::unordered_map<int, std::unordered_map<int, int>> global_map;
std::unordered_map<int, int> process;

const int BLOCK_SIZE = 800;
const int MOD = 1e9 + 7;
const int N = 1e7;
int lp[N] = {0};

void lp_fill() {
    std::vector<int> pr;
    for (int i = 0; i < N; ++i) lp[i] = 0;
    for (int i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (int p : pr) {
            if (lp[i] < p || i*p >= N) break;
            lp[i*p] = p;
        }
    }
}

void get_dividers(std::unordered_map<int, int>& mp, int a) {
    while(a > 1) {
        mp[lp[a]]++;
        a = a/lp[a];
    }
}

void GetGlobalMap(std::vector<int>& vec) {
    for (int num : vec) {
        if (global_map.count(num)) continue;

        std::unordered_map<int, int> add;
        get_dividers(add, num);
        global_map[num] = add;
    }
}

struct Query {
    int l, r, idx;

    bool operator<(const Query& other) const {
        if (l / BLOCK_SIZE != other.l / BLOCK_SIZE) return l < other.l;
        return r < other.r;
    }
};

void add(int number) {
    for (auto& [num, count] : global_map[number]) {
        process[num] += count;
    }
}

void remove(int number) {
    for (auto& [num, count] : global_map[number]) {
        process[num] -= count;

        if (process[num] == 0) process.erase(num);
    }
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    lp_fill();

    int n, q;
    std::cin >> n >> q;
    std::vector<int> a(n);
    std::vector<Query> queries;
    for (int i = 0; i < n; ++i) std::cin >> a[i];
    for (int i = 0; i < q; ++i) {
        int l, r;
        std::cin >> l >> r;
        queries.emplace_back(l - 1, r - 1, i);
    }
    GetGlobalMap(a);

    std::vector<Query> sorted_queries = queries;
    std::sort(sorted_queries.begin(), sorted_queries.end());
    std::vector<int> answers(q);

    int l = 0; int r = -1;

    for (auto& query : sorted_queries) {
        while (l > query.l) {
            add(a[l - 1]);
            --l;
        }

        while (l < query.l) {
            remove(a[l]);
            ++l;
        }

        while (r > query.r) {
            remove(a[r]);
            --r;
        }

        while (r < query.r) {
            add(a[r + 1]);
            ++r;
        }

        int ans = 1;
        for (auto& [num, count] : process) {
            ans = (ans * (count + 1)) % MOD;
        }
        answers[query.idx] = ans;
    }

    for (int num : answers) std::cout << num << '\n';
}
