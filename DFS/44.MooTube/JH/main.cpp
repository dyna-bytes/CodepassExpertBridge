#include <stdio.h>
#include <string.h>
#define DBG 1
#if DBG
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#define debugArr(A, N) do { \
    printf("[%s](%d) %s is |", __func__, __LINE__, #A); \
    for (int i = 0; i < N; i++) printf("%d|", A[i]); \
    printf("\n"); \
} while (0)
#define debugArr2D(AA, Y, X) do { \
    printf("[%s](%d) %s is \n", __func__, __LINE__, #AA); \
    for (int y = 0; y < Y; y++) debugArr(AA[y], X); \
    printf("\n"); \
} while (0)
#else
#define debug(x)
#define debugArr(A, N)
#define debugArr2D(AA, Y, X)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

struct point_t {
    int to;
    int val;
};

const int INF = 1e9 + 7;
const int MAXN = 5000 + 10;
int N, Q;
point_t adj[MAXN][MAXN];
int sp[MAXN];
int visited[MAXN];
int scores[MAXN];

void dfs(int curr, int val) {
    scores[curr] = val;
    for (int i = 0; i < sp[curr]; i++) {
        auto [next, weight] = adj[curr][i];
        if (visited[next]) continue;
        visited[next] = true;
        dfs(next, min(val, weight));
    }
}

int query(int k, int v) {
    memset(visited, 0, sizeof(visited));
    memset(scores, 0, sizeof(scores));
    visited[v] = true;
    dfs(v, INF);
    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        if (i == v) continue;
        if (scores[i] >= k) cnt++;
    }
    return cnt;
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < N-1; i++) {
        int p, q, r;
        scanf("%d %d %d", &p, &q, &r);
        adj[p][sp[p]++] = {q, r};
        adj[q][sp[q]++] = {p, r};
    }
    for (int i = 0; i < Q; i++) {
        int k, v;
        scanf("%d %d", &k, &v);

        int ret = query(k, v);
        printf("%d\n", ret);
    }
    return 0;
}