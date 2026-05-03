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

const int MAXN = 15;

int N;
int x_map[MAXN];
int left_offset_map[MAXN * 2 + 1]; // lom[b + MAXN] = true, where y = x + b <-> b = y - x
int right_offset_map[MAXN * 2 + 1]; // rom[b] = true, where y = -x + b <-> b = y + x

int dfs(int y) {
    if (y == N) return true;

    int ret = 0;
    for (int x = 0; x < N; x++) {
        if (x_map[x]) continue;
        if (left_offset_map[y - x + MAXN]) continue;
        if (right_offset_map[y + x]) continue;

        x_map[x] = true;
        left_offset_map[y - x + MAXN] = true;
        right_offset_map[y + x] = true;

        ret += dfs(y + 1);

        x_map[x] = false;
        left_offset_map[y - x + MAXN] = false;
        right_offset_map[y + x] = false;
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    int ret = dfs(0);

    printf("%d", ret);
    return 0;
}