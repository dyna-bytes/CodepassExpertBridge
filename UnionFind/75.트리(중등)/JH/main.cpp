#include <stdio.h>
#include <memory.h>
#define debug(x) printf("%s is %d\n", #x, x);

const int MAXN = 2e5 + 5;

struct disjoint_set {
    int parent[MAXN];

    void init() {
        memset(parent, -1, sizeof(parent));
    }
    int find(int x) {
        if (parent[x] < 0) return x;
        return parent[x] = find(parent[x]);
    }
    int merge(int u, int v) {
        u = find(u);
        v = find(v);
        if (u == v) return false;
        parent[u] = v;
        return true;
    }
};

struct query_t {
    int type;
    int u, v;
};

int N;
int Q;
int parent[MAXN];
query_t queries[MAXN * 2];
int ret[MAXN];
int ret_sz;

void solve() {
    disjoint_set uf;
    uf.init();

    for (int i = (N-1) + Q; i >= 0; i--) {
        if (queries[i].type == 0) {
            uf.merge(queries[i].u, queries[i].v);
        } else {
            ret[ret_sz++] = (uf.find(queries[i].u) == uf.find(queries[i].v));
        }
    }

    for (int i = ret_sz-1; i >= 0; i--)
        printf("%s\n", (ret[i] ? "YES" : "NO"));
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 1; i <= N-1; i++) {
        int u = i + 1;
        int p;
        scanf("%d", &p);
        parent[u] = p;
    }

    for (int i = 0; i < (N-1) + Q; i++) {
        int x, u, v;
        scanf("%d", &x);
        if (x == 0) {
            scanf("%d", &u);
            v = parent[u];
        } else {
            scanf("%d %d", &u, &v);
        }

        queries[i] = {x, u, v};
    }
    solve();
    return 0;
}