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

const int MAXN = 11;

int N;
int l_map[2*MAXN + 1]; // l_map[b + MAXN], where b = y - x
int r_map[2*MAXN + 1]; // r_map[b], where b = y + x
int board[MAXN][MAXN];

int max_bishops;

int dfs(int y_x, int bishops) {
    if (y_x >= N * N) {
        max_bishops = max(max_bishops, bishops);
        return true;
    }

    int y = y_x / N;
    int x = y_x % N;
    int odd = (y + x) % 2;
    int next_y_x;
    for (next_y_x = y_x + 1; true; next_y_x++) {
        int next_y = next_y_x / N;
        int next_x = next_y_x % N;
        if ((next_y + next_x) % 2 == odd)
            break;
    }

    if (max_bishops >= bishops + (N * N - y_x))
        return false;

    if (!board[y][x])
        return dfs(next_y_x, bishops);

    if (l_map[y - x + MAXN] || r_map[y + x])
        return dfs(next_y_x, bishops);

    int ret = 0;
    l_map[y - x + MAXN] = true;
    r_map[y + x] = true;

    dfs(next_y_x, bishops + 1);

    l_map[y - x + MAXN] = false;
    r_map[y + x] = false;

    dfs(next_y_x, bishops);
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%d", &board[y][x]);


    dfs(0, 0);
    int ret = max_bishops;
    max_bishops = 0;
    dfs(1, 0);
    ret += max_bishops;

    printf("%d", ret);
    return 0;
}