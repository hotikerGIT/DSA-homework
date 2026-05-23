#include <iostream>
#include <vector>
#include <map>
#include <functional>
#define int long long

/* Идея:
 * в каждой вершине храним счетчик - соклько раз в ее поддерве была встречена вершина которая используется в итом запросе
 * тогда для каждой вершины посчитаем сколько раз она будет являться лса для этого запроса
 * она является лса елспм в двух ее сыновьях есть метка запроса (то есть две вершины в разных поддеревьях)
 */

struct Query {
    int id, k, answer = 0;
    std::vector<int> vertices;
};

struct Vertex {
    int id = 0;
    std::map<int, int> query_counter;
};

signed main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> graph(n + 1);
    std::vector<Vertex> vertices(n + 1);
    for (int i = 1; i <= n; ++i) {
        vertices[i].id = i;
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b, w;
        std::cin >> a >> b >> w;
        graph[a].push_back(b);
    }

    int q;
    std::cin >> q;
    std::vector<Query> queries(q);
    for (int i = 0; i < q; ++i) {
        int k;
        std::cin >> k;

        queries[i].id = i;
        queries[i].k = k;

        for (int j = 0; j < k; ++j) {
            int u;
            std::cin >> u;
            queries[i].vertices.push_back(u);
            vertices[u].query_counter[i]++;
        }
    }

    std::function<void(int, int)> dfs = [&](int cur, int prev) {
        // спустились в листы, затем считаем
        for (int next : graph[cur]) {
            if (next != prev) {
                dfs(next, cur);
            }
        }

        for (int child : graph[cur]) {
            for (auto& [query_id, count] : vertices[child].query_counter) {
                vertices[cur].query_counter[query_id] += vertices[child].query_counter[query_id];
            }
        }

        for (int child : graph[cur]) {
            for (auto& [query_id, count] : vertices[child].query_counter) {
                int child_count = vertices[child].query_counter[query_id];
                int cur_count = vertices[cur].query_counter[query_id];
                queries[query_id].answer += cur * (cur_count - child_count) * child_count;
            }
        }
    };
    dfs(1, -1);

    for (auto& query : queries) {
        std::cout << query.answer << '\n';
    }
}