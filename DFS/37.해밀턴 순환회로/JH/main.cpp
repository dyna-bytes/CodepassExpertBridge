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

const int INF = 1e9 + 7;
const int MAXN = 15;

int N;
int adj[MAXN][MAXN];
int min_cost = INF;

int P(int n, int k, int stack[], int sp, int visited[], int cost) {
    if (k == 0) {
        int dist = adj[stack[sp - 1]][0];

        if (dist == 0) return 0;

        min_cost = min(min_cost, cost + dist);
        return 1;
    }

    int ret = 0;
    for (int i = 0; i < n; i++) {
        int dist = adj[stack[sp - 1]][i];

        if (dist == 0) continue;
        if (min_cost <= cost + dist) continue;
        if (visited[i]) continue;

        visited[i] = true;
        stack[sp++] = i;
        ret += P(n, k-1, stack, sp, visited, cost + dist);
        sp--;
        visited[i] = false;
    }
    return ret;
}

int stack[MAXN] = {};
int visited[MAXN] = {};
int solve() {
    stack[0] = 0; // start point fixed
    visited[0] = true;
    P(N, N-1, stack, 1, visited, 0);

    return min_cost;
}

int main() {
    scanf("%d", &N);
    for (int from = 0; from < N; from++)
        for (int to = 0; to < N; to++)
            scanf("%d", &adj[from][to]);

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}