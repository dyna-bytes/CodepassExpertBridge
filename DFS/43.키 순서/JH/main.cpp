#include <stdio.h>
#include <string.h>
#define DBG 0
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

const int MAXN = 500 + 10;

int N, M;
int adj[MAXN][MAXN];
int sp[MAXN];

int inv[MAXN][MAXN];
int isp[MAXN];

int visited[MAXN];
int dfs(int curr) {
    int ret = 1;

    for (int i = 0; i < sp[curr]; i++) {
        int next = adj[curr][i];
        if (visited[next]) continue;
        visited[next] = true;
        ret += dfs(next);
    }
    return ret;
}

int idp[MAXN];
int idfs(int curr) {
    int ret = 1;

    for (int i = 0; i < isp[curr]; i++) {
        int next = inv[curr][i];
        if (visited[next]) continue;
        visited[next] = true;
        ret += idfs(next);
    }
    return ret;
}

int solve() {
    int ret = 0;
    for (int i = 1; i <= N; i++) {
        memset(visited, 0, sizeof(visited));
        visited[i] = true;
        int tallers = dfs(i);

        memset(visited, 0, sizeof(visited));
        visited[i] = true;
        int shorters = idfs(i);

        if (tallers + shorters == N + 1)
            ret++;
    }
    return ret;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][sp[u]++] = v;
        inv[v][isp[v]++] = u;
    }

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}