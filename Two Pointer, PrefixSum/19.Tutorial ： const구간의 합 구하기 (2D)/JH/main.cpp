#include <stdio.h>
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

typedef long long ll;
const int MAXN = 1e3 + 10;

ll grid[MAXN][MAXN];
ll pref[MAXN][MAXN];

int main() {
    int N; scanf("%d", &N);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%lld", &grid[y][x]);

    for (int y = 1; y <= N; y++)
        for (int x = 1; x <= N; x++)
            pref[y][x] = grid[y-1][x-1] + pref[y][x-1] + pref[y-1][x] - pref[y-1][x-1];

    int Q; scanf("%d", &Q);
    for (int i = 0; i < Q; i++) {
        int sy, sx, ey, ex;
        scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
        sy--, sx--;
        printf("%lld\n", pref[ey][ex] - pref[ey][sx] - pref[sy][ex] + pref[sy][sx]);
    }

    return 0;
}