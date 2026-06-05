#include <stdio.h>
#include <memory.h>
#define debug(x) printf("%s is %d\n", #x, x);
const int MAXN = 5e4 + 5;

struct disjoint_set {
    int parent[MAXN];

    void init() {
        memset(parent, -1, sizeof(parent));
    }
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    void merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return;

        parent[u] += parent[v];
        parent[v] = u;
    }
    int size(int x) {
        return -parent[find(x)];
    }
};

int main() {
    int N, Q;
    disjoint_set uf;
    uf.init();

    scanf("%d %d", &N, &Q);
    for (int i = 0; i < Q; i++) {
        int t, x, y;
        scanf("%d", &t);
        if (t == 1) {
            scanf("%d %d", &x, &y);
            uf.merge(x, y);
        } else {
            scanf("%d", &x);
            printf("%d\n", uf.size(x));
        }
    }
    return 0;
}