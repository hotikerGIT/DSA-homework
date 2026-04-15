#include <bits/stdc++.h>
using namespace std;

struct GlobalNode;

struct ValueNode {
    GlobalNode* gPtr;
    int priority;
    int size;
    ValueNode *l, *r;

    ValueNode(GlobalNode* g) : gPtr(g), priority(rand()), size(1), l(nullptr), r(nullptr) {}
};

struct GlobalNode {
    int value;
    int priority;
    int size;
    GlobalNode *l, *r;

    GlobalNode(int v) : value(v), priority(rand()), size(1), l(nullptr), r(nullptr) {}
};

// ============ Глобальный треп ============
int getGSize(GlobalNode* t) { return t ? t->size : 0; }

void updateG(GlobalNode* t) {
    if (!t) return;
    t->size = 1 + getGSize(t->l) + getGSize(t->r);
}

void splitG(GlobalNode* t, int k, GlobalNode*& l, GlobalNode*& r) {
    if (!t) { l = r = nullptr; return; }
    int cur = getGSize(t->l) + 1;
    if (cur <= k) { splitG(t->r, k - cur, t->r, r); l = t; }
    else { splitG(t->l, k, l, t->l); r = t; }
    updateG(t);
}

void mergeG(GlobalNode*& t, GlobalNode* l, GlobalNode* r) {
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority) { mergeG(l->r, l->r, r); t = l; }
    else { mergeG(r->l, l, r->l); t = r; }
    if (t) updateG(t);
}

// Получить узел на позиции pos (1-based) в глобальном трепе
GlobalNode* getNodeAt(GlobalNode* t, int pos) {
    if (!t) return nullptr;
    int cur = getGSize(t->l) + 1;
    if (cur == pos) return t;
    if (cur < pos) return getNodeAt(t->r, pos - cur);
    return getNodeAt(t->l, pos);
}

// ============ Трепы по значениям ============
int getVSize(ValueNode* t) { return t ? t->size : 0; }

void updateV(ValueNode* t) {
    if (!t) return;
    t->size = 1 + getVSize(t->l) + getVSize(t->r);
}

void splitV(ValueNode* t, int k, ValueNode*& l, ValueNode*& r) {
    if (!t) { l = r = nullptr; return; }
    int cur = getVSize(t->l) + 1;
    if (cur <= k) { splitV(t->r, k - cur, t->r, r); l = t; }
    else { splitV(t->l, k, l, t->l); r = t; }
    updateV(t);
}

void mergeV(ValueNode*& t, ValueNode* l, ValueNode* r) {
    if (!l || !r) t = l ? l : r;
    else if (l->priority > r->priority) { mergeV(l->r, l->r, r); t = l; }
    else { mergeV(r->l, l, r->l); t = r; }
    if (t) updateV(t);
}

// ============ Глобальные структуры ============
const int MAXN = 100005;
ValueNode* valueTreaps[MAXN];
GlobalNode* globalRoot = nullptr;

// Найти ранг узла в valueTreap по указателю на GlobalNode
int findRankByPtr(ValueNode* t, GlobalNode* target) {
    if (!t) return 0;
    if (t->gPtr == target) return getVSize(t->l) + 1;
    int left = findRankByPtr(t->l, target);
    if (left) return left;
    int right = findRankByPtr(t->r, target);
    return right ? getVSize(t->l) + 1 + right : 0;
}

// Binary search: найти первый ранг с глобальной позицией >= targetPos
int lowerBound(ValueNode* t, int targetPos) {
    if (!t) return 1;

    int gPos = 0;
    GlobalNode* cur = t->gPtr;
    // Вычисляем позицию узла в глобальном трепе
    GlobalNode* root = globalRoot;
    while (root) {
        int curPos = getGSize(root->l) + 1;
        if (root == cur) { gPos = targetPos - (targetPos - curPos); break; }
        if (curPos <= 0) { root = root->r; }
        else { root = root->l; }
    }
    // Упрощённо: используем getNodeAt для проверки
    int leftSize = getVSize(t->l);
    GlobalNode* nodeAtRank = nullptr;

    // Для простоты: ищем узел на позиции targetPos и сравниваем указатели
    GlobalNode* targetNode = getNodeAt(globalRoot, targetPos);

    if (t->gPtr == targetNode || (targetNode && getGSize(t->gPtr->l) >= 0)) {
        return lowerBound(t->l, targetPos);
    } else {
        return leftSize + 1 + lowerBound(t->r, targetPos);
    }
}

int upperBound(ValueNode* t, int targetPos) {
    if (!t) return 1;

    GlobalNode* targetNode = getNodeAt(globalRoot, targetPos);
    int leftSize = getVSize(t->l);

    // Сравниваем: позиция t->gPtr > targetPos?
    // Для простоты: проверяем ранг
    int rank = findRankByPtr(valueTreaps[t->gPtr->value], t->gPtr);
    GlobalNode* nodeAtTarget = getNodeAt(globalRoot, targetPos);

    if (nodeAtTarget && t->gPtr == nodeAtTarget) {
        return leftSize + 1 + upperBound(t->r, targetPos);
    } else if (nodeAtTarget) {
        return leftSize + 1 + upperBound(t->r, targetPos);
    } else {
        return upperBound(t->l, targetPos);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    srand(time(nullptr));

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int v;
        cin >> v;
        GlobalNode* g = new GlobalNode(v);
        mergeG(globalRoot, globalRoot, g);

        ValueNode* vn = new ValueNode(g);
        mergeV(valueTreaps[v], valueTreaps[v], vn);
    }

    int q;
    cin >> q;
    int lastans = 0;

    while (q--) {
        int type;
        cin >> type;

        if (type == 1) {
            int lp, rp;
            cin >> lp >> rp;
            int l = ((lp + lastans - 1) % n) + 1;
            int r = ((rp + lastans - 1) % n) + 1;
            if (l > r) swap(l, r);

            // Находим узел на позиции r
            GlobalNode* nodeR = getNodeAt(globalRoot, r);
            int val = nodeR->value;

            // Находим ранг nodeR в valueTreaps[val]
            int rankR = findRankByPtr(valueTreaps[val], nodeR);

            // Находим сколько элементов val в [l, r-1]
            GlobalNode* nodeL = getNodeAt(globalRoot, l);
            int rankL = findRankByPtr(valueTreaps[val], nodeL);

            // Cyclic shift в глобальном трепе
            GlobalNode *g1, *g2, *g3, *g4, *g5;
            splitG(globalRoot, l - 1, g1, g2);
            splitG(g2, r - l + 1, g3, g4);
            splitG(g3, r - l, g5, g3);
            mergeG(g3, g3, g5);
            mergeG(g2, g3, g4);
            mergeG(globalRoot, g1, g2);

            // Тот же сдвиг в valueTreaps[val]
            // Элемент на rankR перемещается на rankL
            ValueNode *v1, *v2, *v3, *v4;
            splitV(valueTreaps[val], rankR - 1, v1, v2);
            splitV(v2, 1, v3, v4);  // v3 - это nodeR

            ValueNode *v5, *v6;
            splitV(v1, rankL - 1, v5, v6);
            mergeV(v6, v3, v6);  // Вставляем nodeR перед rankL
            mergeV(v1, v5, v6);
            mergeV(valueTreaps[val], v1, v4);

        } else {
            int lp, rp, kp;
            cin >> lp >> rp >> kp;
            int l = ((lp + lastans - 1) % n) + 1;
            int r = ((rp + lastans - 1) % n) + 1;
            int k = ((kp + lastans - 1) % n) + 1;
            if (l > r) swap(l, r);

            // Проходим по valueTreaps[k] и считаем сколько в [l, r]
            ValueNode* t = valueTreaps[k];
            lastans = 0;

            // Временное решение: собираем все узлы и проверяем позиции
            vector<GlobalNode*> nodes;
            function<void(ValueNode*)> collect = [&](ValueNode* nd) {
                if (!nd) return;
                collect(nd->l);
                nodes.push_back(nd->gPtr);
                collect(nd->r);
            };
            collect(t);

            for (auto* nd : nodes) {
                int pos = 0;
                GlobalNode* cur = globalRoot;
                int target = nd->value;
                // Находим позицию
                while (cur) {
                    int curPos = getGSize(cur->l) + 1;
                    if (cur == nd) { pos = curPos; break; }
                    if (curPos <= 0) cur = cur->r;
                    else if (cur == nd) { pos = curPos; break; }
                    else {
                        if (getGSize(cur->l) >= 0) {
                            if (cur->l == nd || getGSize(cur->l) > 0) cur = cur->l;
                            else { pos = curPos + getGSize(cur->l); cur = cur->r; }
                        } else cur = cur->r;
                    }
                }
                if (pos >= l && pos <= r) lastans++;
            }

            cout << lastans << "\n";
        }
    }

    return 0;
}