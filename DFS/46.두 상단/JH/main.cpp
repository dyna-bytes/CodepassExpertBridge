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

const int MAXN = 10 + 1;
const int INF = 1e9 + 7;

int N;
int A[MAXN];
int adj[MAXN][MAXN];
int visited[MAXN];

int group[MAXN];
int min_ans = INF;

void C(int n, int k, int prev, int (*do_solve)(void)) {
    if (k == 0) {
        debugArr(group, N);
        int ans = do_solve();
        debug(ans);
        min_ans = min(min_ans, ans);
        return;
    }

    for (int next = prev + 1; next < n; next++) {
        group[next] = true;
        C(n, k-1, next, do_solve);
        group[next] = false;
    }
}

void dfs(int curr, bool group_flag) {

    for (int next = 0; next < N; next++) {
        if (adj[curr][next] == false) continue;
        if (group[next] != group_flag) continue;
        if (visited[next]) continue;
        visited[next] = true;
        dfs(next, group_flag);
    }
}

int do_solve() {
    memset(visited, 0, sizeof(visited));
    visited[0] = true;
    int group_flag = group[0];
    dfs(0, group_flag);

    if (group_flag)
        for (int i = 0; i < N; i++) {
            if (group[i] != visited[i]) {
                debugArr(visited, N);
                return INF;
            }
        }
    else
        for (int i = 0; i < N; i++) {
            if (group[i] == visited[i]) {
                debugArr(visited, N);
                return INF;
            }
        }

    int other;
    for (other = 1; other < N; other++)
        if (group[0] != group[other]) break;
    debug(other);

    memset(visited, 0, sizeof(visited));
    visited[other] = true;
    group_flag = group[other];
    dfs(other, group_flag);

    if (group_flag)
        for (int i = 0; i < N; i++) {
            if (group[i] != visited[i]) {
                debugArr(visited, N);
                return INF;
            }
        }
    else
        for (int i = 0; i < N; i++) {
            if (group[i] == visited[i]) {
                debugArr(visited, N);
                return INF;
            }
        }

    int a_sum = 0;
    int b_sum = 0;
    for (int i = 0; i < N; i++) {
        if (group[i]) a_sum += A[i];
        else b_sum += A[i];
    }
    return abs(a_sum - b_sum);
}

int solve() {
    for (int k = 1; k < N; k++) {
        C(N, k, -1, do_solve);
    }

    if (min_ans == INF) return -1;
    return min_ans;
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);
    for (int from = 0; from < N; from++) {
        int M;
        scanf("%d", &M);
        for (int i = 0; i < M; i++) {
            int to;
            scanf("%d", &to);
            --to;
            adj[from][to] = adj[to][from] = true;
        }
    }
    debugArr2D(adj, N, N);

    int ret = solve();
    printf("%d", ret);
    return 0;
}