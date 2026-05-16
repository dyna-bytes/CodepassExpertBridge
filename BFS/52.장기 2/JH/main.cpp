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

const int dy[] = {-2, -1, 1, 2, 2, 1, -1, -2};
const int dx[] = {1, 2, 2, 1, -1, -2, -2, -1};
const int MAXN = 1000 + 10;
int Y, X;
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 < y && y <= Y && 0 < x && x <= X;
}

int qy[MAXN * MAXN] = {};
int qx[MAXN * MAXN] = {};
int eq = 0, dq = 0;
int bfs(int sy, int sx, int ey, int ex) {

    qy[eq] = sy, qx[eq] = sx;
    eq++;

    int time = 0;
    while (dq < eq) {
        int qsize = eq - dq;
        for (int step = 0; step < qsize; step++) {
            int y = qy[dq], x = qx[dq];
            dq++;

            if (y == ey && x == ex) return time;

            for (int d = 0; d < 8; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (visited[ny][nx]) continue;
                visited[ny][nx] = true;
                qy[eq] = ny, qx[eq] = nx;
                eq++;
            }
        }
        time++;
    }

    return -1;
}

int main() {
    scanf("%d %d", &Y, &X);
    int sy, sx, ey, ex;
    scanf("%d %d %d %d", &sy, &sx, &ey, &ex);
    int ret = bfs(sy, sx, ey, ex);
    printf("%d\n", ret);
    return 0;
}