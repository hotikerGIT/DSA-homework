#include <vector>
#include <iostream>
#include <queue>
#define int long long

class Graph {
private:
    std::vector<std::vector<std::pair<int, int>>> g;
    int n;
    int tree_n;

    int base_out;
    int base_in;

    int out_root;
    int in_root;

    void build_out(int node, int l, int r) {
        if (l == r) {
            g[base_out + node].emplace_back(l, 0);
            return;
        }

        int mid = (l + r) / 2;
        int left = node * 2;
        int right = node * 2 + 1;

        g[base_out + node].emplace_back(base_out + left, 0);
        g[base_out + node].emplace_back(base_out + right, 0);

        build_out(left, l, mid);
        build_out(right, mid + 1, r);
    }

    void build_in(int node, int l, int r) {
        if (l == r) {
            g[l].emplace_back(base_in + node, 0);
            return;
        }

        int mid = (l + r) / 2;
        int left = node * 2;
        int right = node * 2 + 1;

        g[base_in + left].emplace_back(base_in + node, 0);
        g[base_in + right].emplace_back(base_in + node, 0);

        build_in(left, l, mid);
        build_in(right, mid + 1, r);
    }

    void add_out(int v, int ql, int qr, int node, int l, int r, int w) {
        if (ql <= l && r <= qr) {
            g[v].emplace_back(base_out + node, w);
            return;
        }

        int mid = (l + r) / 2;
        if (ql <= mid) add_out(v, ql, qr, node * 2, l, mid, w);
        if (qr > mid) add_out(v, ql, qr, node * 2 + 1, mid + 1, r, w);
    }

    void add_in(int ql, int qr, int v, int node, int l, int r, int w) {
        if (ql <= l && r <= qr) {
            g[base_in + node].emplace_back(v, w);
            return;
        }

        int mid = (l + r) / 2;
        if (ql <= mid) add_in(ql, qr, v, node * 2, l, mid, w);
        if (qr > mid) add_in(ql, qr, v, node * 2 + 1, mid + 1, r, w);
    }

public:
    Graph(int n_) : n(n_) {
        tree_n = 1;
        while (tree_n < n) tree_n *= 2;

        base_out = n + 1;
        base_in = n + 4 * tree_n + 1;

        int total_size = base_in + 4 * tree_n + 5;
        g.resize(total_size);

        out_root = 1;
        in_root = 1;

        build_out(out_root, 1, n);
        build_in(in_root, 1, n);
    }

    void add_edge_type1(int v, int u, int w) {
        g[v].emplace_back(u, w);
    }

    void add_edge_type2(int v, int l, int r, int w) {
        add_out(v, l, r, out_root, 1, n, w);
    }

    void add_edge_type3(int v, int l, int r, int w) {
        add_in(l, r, v, in_root, 1, n, w);
    }

    std::vector<int> dijkstra(int start) {
        std::vector<int> dist(g.size(), 1e18);
        dist[start] = 0;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<>> pq;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto [d, u] = pq.top();
            pq.pop();
            if (d != dist[u]) continue;
            for (auto [to, w] : g[u]) {
                if (dist[to] > d + w) {
                    dist[to] = d + w;
                    pq.emplace(dist[to], to);
                }
            }
        }

        std::vector<int> result(n + 1);
        for (int i = 1; i <= n; ++i) {
            if (dist[i] >= 1e18) result[i] = -1;
            else result[i] = dist[i];
        }
        return result;
    }
};

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n, q, s;
    std::cin >> n >> q >> s;

    Graph graph(n);

    for (int i = 0; i < q; ++i) {
        int t;
        std::cin >> t;

        if (t == 1) {
            int v, u, w;
            std::cin >> v >> u >> w;
            graph.add_edge_type1(v, u, w);

        } else if (t == 2) {
            int v, l, r, w;
            std::cin >> v >> l >> r >> w;
            graph.add_edge_type2(v, l, r, w);

        } else {
            int v, l, r, w;
            std::cin >> v >> l >> r >> w;
            graph.add_edge_type3(v, l, r, w);
        }
    }

    std::vector<int> ans = graph.dijkstra(s);

    for (int i = 1; i <= n; ++i) {
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";
}