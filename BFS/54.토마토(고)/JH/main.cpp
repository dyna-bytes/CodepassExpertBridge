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

const int MAXN = 100 + 5;
const int dz[6] = {-1, 1, 0, 0, 0, 0};
const int dy[6] = {0, 0, 1, 0, -1, 0};
const int dx[6] = {0, 0, 0, 1, 0, -1};
int Z, Y, X;
int board[MAXN][MAXN][MAXN];
int visited[MAXN][MAXN][MAXN];

bool inRange(int z, int y, int x) {
    return (0 <= z && z < Z)
    && (0 <= y && y < Y)
    && (0 <= x && x < X);
}

struct node_t {
    int z, y, x;
};

node_t q[MAXN * MAXN * MAXN];
int dq = 0, eq = 0;

int bfs() {
    for (int z = 0; z < Z; z++)
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                if (board[z][y][x] == 1) {
                    q[eq++] = {z, y, x};
                    visited[z][y][x] = true;
                }

    int step = -1;
    while (dq < eq) {
        int qsize = eq - dq;
        for (int k = 0; k < qsize; k++) {
            auto [z, y, x] = q[dq++];

            for (int d = 0; d < 6; d++) {
                int nz = z + dz[d];
                int ny = y + dy[d];
                int nx = x + dx[d];
                if (!inRange(nz, ny, nx)) continue;
                if (board[nz][ny][nx] != 0) continue;
                if (visited[nz][ny][nx]) continue;
                visited[nz][ny][nx] = true;
                board[nz][ny][nx] = 1;
                q[eq++] = {nz, ny, nx};
            }
        }
        step++;
    }

    for (int z = 0; z < Z; z++)
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                if (board[z][y][x] == 0)
                    return -1;

    return step;
}

int main() {
    scanf("%d %d %d", &X, &Y, &Z);
    for (int z = 0; z < Z; z++) {
        for (int y = 0; y < Y; y++)
            for (int x = 0; x < X; x++)
                scanf("%d", &board[z][y][x]);
    }

    int ret = bfs();
    printf("%d\n", ret);
    return 0;
}