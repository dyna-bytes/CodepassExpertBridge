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

const int N = 9;

int board[N][N];
int x_map[N][N+1];
int y_map[N][N+1];
int z_map[N][N+1]; // z = (y / 3) * 3 + (x / 3)

int dfs(int y_x) { // y_x = y * N + x
    if (y_x >= N * N) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x < N; x++)
                printf("%d ", board[y][x]);
            printf("\n");
        }
        return true;
    }

    int y = y_x / N;
    int x = y_x % N;
    int z = (y / 3) * 3 + (x / 3);

    if (board[y][x]) {
        return dfs(y_x + 1);
    }

    for (int i = 1; i <= N; i++) {
        if (x_map[x][i]) continue;
        if (y_map[y][i]) continue;
        if (z_map[z][i]) continue;

        x_map[x][i] = true;
        y_map[y][i] = true;
        z_map[z][i] = true;

        board[y][x] = i;
        if (dfs(y_x + 1))
            return true;

        x_map[x][i] = false;
        y_map[y][i] = false;
        z_map[z][i] = false;
        board[y][x] = 0;
    }

    return false;
}

int main() {
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++) {
            int z = (y / 3) * 3 + (x / 3);
            scanf("%d", &board[y][x]);

            x_map[x][board[y][x]] = true;
            y_map[y][board[y][x]] = true;
            z_map[z][board[y][x]] = true;
        }

    dfs(0);
    return 0;
}