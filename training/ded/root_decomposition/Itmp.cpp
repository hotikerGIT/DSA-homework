#include <unordered_map>
#include <vector>
#include <iostream>


using namespace std;

#define ll long long
#define vll vector<ll>
#define vvll vector<vll>
#define pll pair<ll, ll>
#define pll pair<ll, ll>

struct Block {
    ll size = 0;
    unordered_map<ll, ll> simp;
    vll elements;
};

const ll B = 400;
ll n, q;
ll k; //количество блоков
vector<Block> sqr;
const ll M = 1e9+7;
const ll N = 1e7+1;
ll lp[N] = {0};

void lp_fill() {
    vll pr;
    for (ll i = 0; i < N; ++i) lp[i] = 0;
    for (ll i = 2; i < N; ++i) {
        if (lp[i] == 0) {
            lp[i] = i;
            pr.push_back(i);
        }
        for (ll p : pr) {
            if (lp[i] < p || i*p >= N) break;
            lp[i*p] = p;
        }
    }
}

void get_dividers(unordered_map<ll, ll>& mp, ll a) {
    while(a > 1) {
        mp[lp[a]]++;
        a = a/lp[a];
    } 
}

void input(Block* block, ll siz) {
    block->size = siz;
    block->elements.resize(siz);   
    for (ll i = 0; i < siz; ++i) {
        cin >> block->elements[i];
        get_dividers(block->simp, block->elements[i]);
    }
}

void output(Block* block) {
    cout << "block:\n";
    for (ll el : block->elements) cout << el << " ";
    cout << "\n";
}

pll get_index(ll i) {
    return {i / B, i % B};
}

void query_S_part(Block* block, ll l, ll r, unordered_map<ll, ll>& simples) {
    ll res = 0;
    for (ll i = l; i < r; ++i) {
        get_dividers(simples, block->elements[i]);
    }
}

void query_S_full(Block* block, unordered_map<ll, ll>& simples) {
    for (auto el : block->simp) {
        simples[el.first] += el.second;
    }
}

ll sygma0(unordered_map<ll, ll>& simples) {
    ll res = 1;
    for (auto el : simples) {
        res *= el.second + 1;
        if (res >= M) res %= M;
    }
    return res;
}

ll query() {
    ll l, r;
    cin >> l >> r;
    --l;
    --r;
    auto [l_block, l_ind] = get_index(l);
    auto [r_block, r_ind] = get_index(r);
    unordered_map<ll, ll> simples;
    simples.reserve(1000);
    if (l_block == r_block) {
        query_S_part(&sqr[l_block], l_ind, r_ind+1, simples);
        return sygma0(simples);
    }
    ll res = 0;
    query_S_part(&sqr[l_block], l_ind, sqr[l_block].size, simples);
    query_S_part(&sqr[r_block], 0LL,  r_ind+1, simples);
    for (ll pos = l_block + 1; pos < r_block; ++pos) {
        query_S_full(&sqr[pos], simples);
    }
    return sygma0(simples);
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    lp_fill();
    cin >> n >> q;
    k = (n + B - 1)/ B;
    sqr.resize(k);
    for (ll i = 0; i < n / B; ++i) {
        //ввести все нормальные блоки
        input(&sqr[i], B);
    }

    if (k != n / B) {
        //ввести полседний блок
        input(&sqr[k-1], n % B); 
    }

    while (q--) {
        //выполняем запрос
        cout << query() << "\n";
    }    
    return 0;
}