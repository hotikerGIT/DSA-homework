#include <iostream>
#include <vector>
#include <algorithm>
#define int long long

template <typename Node,
          typename UpdateNode,
          typename Merge,
          typename Update,
          typename Compose>
class SegmentTree {
private:
    std::vector<Node> tree;
    std::vector<UpdateNode> lazy;
    int n = 0;
    Merge merge_;
    Update update_;
    Compose compose_;

private:
    void build(int index, int tree_left, int tree_right, std::vector<Node>& start) {
        if (tree_left == tree_right) {
            tree[index] = start[tree_left];
            return;
        }

        int tree_mid = (tree_left + tree_right) / 2;
        build(index * 2, tree_left, tree_mid, start);
        build(index * 2 + 1, tree_mid + 1, tree_right, start);
        tree[index] = merge_(tree[index * 2], tree[index * 2 + 1]);
    }

    Node get(int index, int tree_left, int tree_right, int wanted) {
        push(index, tree_left, tree_right);

        if (tree_left == tree_right && tree_left == wanted) return tree[index];

        int tree_mid = (tree_left + tree_right) / 2;
        if (wanted <= tree_mid) return get(index * 2, tree_left, tree_mid, wanted);
        return get(index * 2 + 1, tree_mid + 1, tree_right, wanted);
    }

    void update(int index, int tree_left, int tree_right, int left, int right, UpdateNode& update_node) {
        if (left <= tree_left && tree_right <= right) {
            compose_(lazy[index], update_node);
            push(index, tree_left, tree_right);
            return;
        }

        push(index, tree_left, tree_right);

        if (right < tree_left || tree_right < left) return;

        int tree_mid = (tree_left + tree_right) / 2;
        update(index * 2, tree_left, tree_mid, left, right, update_node);
        update(index * 2 + 1, tree_mid + 1, tree_right, left, right, update_node);

        tree[index] = merge_(tree[index * 2], tree[index * 2 + 1]);
    }

    void push(int index, int tree_left, int tree_right) {
        update_(tree[index], lazy[index]);

        if (tree_left != tree_right) {
            compose_(lazy[index * 2], lazy[index]);
            compose_(lazy[index * 2 + 1], lazy[index]);
        }

        lazy[index] = UpdateNode();
    }

public:
    SegmentTree(std::vector<Node>& start,
                Merge merge,
                Update update,
                Compose compose)
                    : n(start.size())
                    , merge_(merge)
                    , update_(update)
                    , compose_(compose) {
        tree.resize(4 * n, Node());
        lazy.resize(4 * n, UpdateNode());
        build(1, 0, n - 1, start);
    }

    SegmentTree() = default;

    void init(std::vector<Node>& start,
                Merge merge,
                Update update,
                Compose compose) {
        n = start.size();
        merge_ = merge;
        update_ = update;
        compose_ = compose;

        tree.assign(4 * n, Node());
        lazy.assign(4 * n, UpdateNode());
        build(1, 0, n - 1, start);
    }

    void update(int left, int right, UpdateNode& update_node) {
        update(1, 0, n - 1, left, right, update_node);
    }

    Node get(int index) {
        return get(1, 0, n - 1, index);
    }
};

template<typename Node>
struct Edge {
    Node from, to;
};

template <typename Node>
struct HeavyPath {
    int id;
    std::vector<Node> state;

    explicit HeavyPath(int id) : id(id) {}

    Node top() const {
        return state.front();
    }
};

template <typename Node,
          typename UpdateNode,
          typename Merge,
          typename Update,
          typename Compose>
class HeavyLightDecomposition {
private:
    using Tree = const std::vector<std::vector<Edge<Node>>>&;
    int n;
    int total_vertices = 0;
    int total_paths = 0;

    std::vector<HeavyPath<Node>> paths_;
    std::vector<int> path_ids_;
    std::vector<int> pos_;

    std::vector<int> size_;
    std::vector<Node> max_child_;
    std::vector<int> depth_;
    std::vector<int> parent_;
    /////////////////
    std::vector<int> last_in_subtree_;

    Merge merge_;
    Update update_;
    Compose compose_;
    SegmentTree<Node, UpdateNode, Merge, Update, Compose> segment_tree_;

private:
    void dfs_sizes(Tree tree, Node cur, Node prev) {
        size_[cur.id] = 1;
        depth_[cur.id] = depth_[prev.id] + 1;
        parent_[cur.id] = prev.id;
        max_child_[cur.id] = Node();

        for (const auto& next : tree[cur.id]) {
            if (next.to.id == prev.id) continue;

            dfs_sizes(tree, next.to, cur);

            size_[cur.id] += size_[next.to.id];

            if (max_child_[cur.id].id == 0 || size_[next.to.id] > size_[max_child_[cur.id].id]) {
                max_child_[cur.id] = next.to;
            }
        }
    }

    void decompose(Tree tree, Node cur, Node prev) {
        path_ids_[cur.id] = total_paths;
        pos_[cur.id] = total_vertices;
        paths_[total_paths].state.push_back(cur);
        total_vertices++;

        if (max_child_[cur.id].id != 0) {
            decompose(tree, max_child_[cur.id], cur);
        }

        for (const auto& next : tree[cur.id]) {
            if (next.to.id == prev.id || next.to.id == max_child_[cur.id].id) continue;

            ++total_paths;
            paths_.emplace_back(total_paths);
            decompose(tree, next.to, cur);
        }

        last_in_subtree_[cur.id] = total_vertices - 1;
    }

    void init_segment_tree() {
        std::vector<Node> array(n);

        int index = 0;
        for (const auto& path : paths_) {
            for (const auto& node : path.state) {
                array[index] = node;
                index++;
            }
        }

        segment_tree_.init(array, merge_, update_, compose_);
    }

    Node query(int u) {
        return segment_tree_.get(pos_[u]);
    }

    void update(int u, int v, UpdateNode updater) {
        while (path_ids_[u] != path_ids_[v]) {
            if (depth_[paths_[path_ids_[u]].top().id] < depth_[paths_[path_ids_[v]].top().id]) {
                std::swap(u, v);
            }

            int path_id = path_ids_[u];
            int top = paths_[path_id].top().id;

            segment_tree_.update(pos_[top], pos_[u], updater);
            u = parent_[top];
        }

        int left = pos_[u];
        int right = pos_[v];
        if (left > right) std::swap(left, right);
        segment_tree_.update(left, right, updater);
    }

    void direct_update(int left, int right, UpdateNode updater) {
        if (left > right) std::swap(left, right);
        segment_tree_.update(left, right, updater);
    }

public:
    explicit HeavyLightDecomposition(Tree tree, Merge merge, Update update, Compose compose)
        : n((int)tree.size() - 1)
        , merge_(merge)
        , update_(update)
        , compose_(compose) {

        paths_.emplace_back(0);
        path_ids_.resize(n + 1, -1);
        pos_.resize(n + 1, -1);
        size_.resize(n + 1, 0);
        max_child_.resize(n + 1, Node());
        depth_.resize(n + 1, 0);
        parent_.resize(n + 1, 0);
        last_in_subtree_.resize(n + 1, 0);

        dfs_sizes(tree, Node(1), Node());
        decompose(tree, Node(1), Node());
        init_segment_tree();
    }

    Node query_path(int u) {
        return query(u);
    }

    void set_subtree(int u, UpdateNode& updater) {
        direct_update(pos_[u], last_in_subtree_[u], updater);
    }

    void set_path_to_root(int u, UpdateNode& updater) {
        update(u, 1, updater);
    }
};

struct Node {
    int id = 0;
    bool is_filled = false;
};

struct UpdateNode {
    int to_set_exact_vertex = -1;
};

Node Merge(const Node& node1, const Node& node2) {
    Node res;
    res.is_filled = false;

    // пофиг?
    // ну типа мы никогда не спрашиваем значение в не-листовой для дерева отрезков вершине
    // все вершины которые нас интересуют покрывают интервал (u-u) то есть лист в ДО

    return res;
}

void Compose(UpdateNode& node1, const UpdateNode& node2) {

    if (node2.to_set_exact_vertex != -1) {
        node1.to_set_exact_vertex = node2.to_set_exact_vertex;
    }
}

void Update(Node& node, const UpdateNode& update_node) {
    if (update_node.to_set_exact_vertex == -1) return;
    node.is_filled = update_node.to_set_exact_vertex;
}

signed main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<std::vector<Edge<Node>>> graph(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        std::cin >> a >> b;
        graph[a].emplace_back(Node(a, false), Node(b, false));
        graph[b].emplace_back(Node(b, false), Node(a, false));
    }

    HeavyLightDecomposition<Node,
                            UpdateNode,
                            decltype(Merge)*,
                            decltype(Update)*,
                            decltype(Compose)*> hld(graph, Merge, Update, Compose);

    int q;
    std::cin >> q;
    for (int i = 0; i < q; ++i) {
        int c, v;
        std::cin >> c >> v;

        if (c == 1) {
            auto updater = UpdateNode(1);
            hld.set_subtree(v, updater);
        }

        if (c == 2) {
            auto updater = UpdateNode(0);
            hld.set_path_to_root(v, updater);
        }

        if (c == 3) {
            std::cout << (int)hld.query_path(v).is_filled << '\n';
        }
    }
}