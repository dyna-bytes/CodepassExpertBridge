#include <stdio.h>
#define DBG 0
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif
#define max(a, b) ((a) > (b) ? (a) : (b))

const int MAXN = 1e3 + 5;
const int MAXM = 1e5 + 5;

int N;
int M;
int adj[MAXN][MAXN];
int sp[MAXN];
int visited[MAXN];

void dfs(int curr) {

    for (int i = 0; i < sp[curr]; i++) {
        int next = adj[curr][i];
        if (visited[next]) continue;
        visited[next] = true;
        dfs(next);
    }
}

int solve() {
    int cnt = 0;
    for (int x = 1; x <= N; x++) {
        if (visited[x]) continue;
        visited[x] = true;
        dfs(x);
        cnt++;
    }
    return cnt;
}

int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        adj[u][sp[u]++] = v;
        adj[v][sp[v]++] = u;
    }

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}
