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

const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
const int MAXN = 100 + 5;

int Y, X;
int visited[MAXN][MAXN];
int grid[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

struct node_t {
    int y, x;
};

node_t q[MAXN * MAXN * MAXN];
int eq = 0, dq = 0;

void bfs(int sy, int sx) {
    memset(visited, 0, sizeof(visited));
    visited[sy][sx] = 4;
    q[eq++] = {sy, sx};

    int time = 0;
    while (dq < eq) {
        int qsize = eq - dq;
        for (int step = 0; step < qsize; step++) {
            auto [y, x] = q[dq++];
            if (visited[y][x] != 3) {
                q[eq++] = {y, x};
                continue;
            }

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (grid[ny][nx] == 0) continue;
                if (visited[ny][nx]) continue;
                visited[ny][nx] = 4;
                q[eq++] = {ny, nx};
            }
        }


        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (visited[y][x] == 0) continue;
                if (--visited[y][x] == 1)
                grid[y][x] = 0;
            }
        }
        time++;
    }

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (visited[y][x] == 0) continue;
            if (--visited[y][x] == 1)
            grid[y][x] = 0;
        }
    }
    time++;

    int survibed = 0;
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            if (grid[y][x]) survibed++;

    printf("%d\n", time);
    printf("%d\n", survibed);
}

int main() {
    scanf("%d %d", &X, &Y);
    for (int y = 0; y < Y; y++) {
        char buf[MAXN];
        scanf("%s", buf);
        for (int x = 0; x < X; x++)
            grid[y][x] = buf[x] - '0';
    }
    int sy, sx;
    scanf("%d %d", &sx, &sy);
    sy--, sx--;
    bfs(sy, sx);
    return 0;
}