/* Кратко, план решения: делаем неявное до по х, в узле храним покрываемый по х отрезок
 * а так же узел - неявное до по у. В нем храним покрываемый отрезок и текущую инверсию, которая едина в каждой точке отрезка
 * Когда получаем запрос на обновление, спускаемся по основному дереву, а потом в каждом
 * узле, который по иксу полностью покрывается запросом,
 * в неявном узле по игреку спускаемся до покрываемого отрезка и инвертируем состояние
 * Когда получаем запрос на значение в точке, спускаемся по основному дереву до узла и каждый узел,
 * который по иксу содержит точку икс, достаем состояние этой точки по игреку (спускаясь по у-узлу и
 * делая хор каждого включающего в себя точку у отрезка)
 * после того как дошли в лист, суммируем все значения и берем мод2
 *
 * это будет работать, потому что природа операции switch это не присваивание, а ХОР,
 * при этом в узлах мы храним, сколько раз конкретный промежуток был изменен
 * тогда, чтобы получить текущее значение в точке, мы должны учесть все lazy изменения,
 * которые происходили в промежутках, содержащих эту точку. Предложенным обходом
 * мы во-первых  не проходим лишнего, а во вторых, не пропускаем нужного
 */

#include <iostream>

struct YNode {
    int left, right;
    int lazy;
    YNode* leftChild;
    YNode* rightChild;

    YNode(int l, int r) : left(l), right(r), lazy(0), leftChild(nullptr), rightChild(nullptr) {}

    void update(int l, int r) {
        if (r < left || right < l) return;
        if (l <= left && right <= r) {
            lazy ^= 1;
            return;
        }

        int mid = (left + right) / 2;

        if (!leftChild) leftChild = new YNode(left, mid);
        if (!rightChild) rightChild = new YNode(mid + 1, right);

        leftChild->update(l, r);
        rightChild->update(l, r);
    }

    int query(int pos) {
        if (left == right) return lazy;

        int mid = (left + right) / 2;

        if (pos <= mid) {
            if (!leftChild) return lazy;
            return lazy ^ leftChild->query(pos);

        } else {
            if (!rightChild) return lazy;
            return lazy ^ rightChild->query(pos);
        }
    }
};

struct XNode {
    int left, right;
    YNode* yTree;
    XNode* leftChild;
    XNode* rightChild;

    XNode(int l, int r) : left(l), right(r), yTree(nullptr), leftChild(nullptr), rightChild(nullptr) {}

    void update(int x1, int x2, int y1, int y2) {
        if (x2 < left || right < x1) return;

        if (x1 <= left && right <= x2) {
            if (!yTree) yTree = new YNode(1, 1000000);
            yTree->update(y1, y2);
            return;
        }

        int mid = (left + right) / 2;

        if (!leftChild) leftChild = new XNode(left, mid);
        if (!rightChild) rightChild = new XNode(mid + 1, right);

        leftChild->update(x1, x2, y1, y2);
        rightChild->update(x1, x2, y1, y2);
    }

    int query(int x, int y) {
        int current = 0;
        if (yTree) current = yTree->query(y);
        if (left == right) return current;

        int mid = (left + right) / 2;
        int child = 0;

        if (x <= mid) {
            if (leftChild) child = leftChild->query(x, y);

        } else {
            if (rightChild) child = rightChild->query(x, y);
        }

        return current ^ child;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int N, M, Q;
    std::cin >> N >> M >> Q;

    auto* root = new XNode(1, N);

    while (Q--) {
        int type;
        std::cin >> type;

        if (type == 1) {
            int x1, y1, x2, y2;
            std::cin >> x1 >> y1 >> x2 >> y2;
            root->update(x1, x2, y1, y2);

        } else {
            int x, y;
            std::cin >> x >> y;
            std::cout << root->query(x, y) << "\n";
        }
    }

    delete root;
    return 0;
}