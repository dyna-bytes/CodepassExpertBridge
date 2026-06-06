#include <stdio.h>
#include <memory.h>
#define debug(x) printf("%s is %d\n", #x, x);

const int MAXN = 100 + 5;

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
        parent[v] += parent[u];
        parent[u] = v;
        return true;
    }
};

struct edge_t {
    int u, v, w;
    bool operator<(const edge_t& other) {
        return w < other.w;
    }
};

int N;
edge_t edges[MAXN * MAXN];
int edges_sz;

edge_t buf[MAXN * MAXN];
void sort(edge_t arr[], int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(arr, s, m);
    sort(arr, m, e);

    int l = s, r = m, k = 0;
    while (l < m && r < e) {
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}
int mst() {
    disjoint_set uf;
    uf.init();

    sort(edges, 0, edges_sz);

    int sum = 0, cnt = 0;
    for (int i = 0; i < edges_sz; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        if (uf.merge(u, v)) {
            sum += w;
            if (++cnt == N) break;
        }
    }

    return sum;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            int w; scanf("%d", &w);
            if (i == j) continue;
            edges[edges_sz++] = {i, j, w};
        }

    int ret = mst();
    printf("%d\n", ret);
    return 0;
}