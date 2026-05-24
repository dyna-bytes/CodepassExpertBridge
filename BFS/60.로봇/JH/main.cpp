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

                // N  E  S  W
const int dy[] = {-1, 0, 1, 0};
const int dx[] = {0, 1, 0, -1};
const int MAXN = 100 + 5;

struct node_t {
    int y, x;
    int dir;

    bool operator == (const node_t& other) {
        return y == other.y && x == other.x && dir == other.dir;
    }
};

int Y, X;
int board[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= x && x < X && 0 <= y && y < Y;
}

int eq, dq;
node_t q[MAXN * MAXN * 4];
bool visited[MAXN][MAXN][4];

int bfs(node_t& begin, node_t& end) {
    q[eq++] = begin;
    visited[begin.y][begin.x][begin.dir] = true;

    int step = 0;
    while (dq < eq) {
        int qsize = eq - dq;
        while (qsize--) {
            node_t curr = q[dq++];
            int y = curr.y, x = curr.x, dir = curr.dir;
            if (curr == end)
                return step;

            for (int d = dir - 1; d <= dir + 1; d++) {
                if (d == dir) continue;
                int ndir = (d + 4) % 4;
                if (visited[y][x][ndir]) continue;
                visited[y][x][ndir] = true;
                q[eq++] = {y, x, ndir};
            }

            for (int k = 1; k <= 3; k++) {
                int ny = y + k * dy[dir];
                int nx = x + k * dx[dir];
                if (!inRange(ny, nx)) continue;
                if (board[ny][nx]) break;;
                if (visited[ny][nx][dir]) continue;
                visited[ny][nx][dir] = true;
                q[eq++] = {ny, nx, dir};
            }
        }
        step++;
    }
    return -1;
}

int main() {
    scanf("%d %d", &Y, &X);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &board[y][x]);

    node_t begin;
    scanf("%d %d %d", &begin.y, &begin.x, &begin.dir);
    begin.dir %= 4;
    if (begin.dir == 2) begin.dir = 3;
    else if (begin.dir == 3) begin.dir = 2;
    begin.y--, begin.x--;

    node_t end;
    scanf("%d %d %d", &end.y, &end.x, &end.dir);
    end.dir %= 4;
    if (end.dir == 2) end.dir = 3;
    else if (end.dir == 3) end.dir = 2;
    end.y--, end.x--;

    int ret = bfs(begin, end);
    printf("%d\n", ret);
    return 0;
}