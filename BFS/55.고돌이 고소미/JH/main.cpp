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

const int dy[9] = {0, -1, -1, 0, 1, 1, 1, 0, -1};
const int dx[9] = {0, 0, 1, 1, 1, 0, -1, -1, -1};
const int MAXN = 25 + 5;

int N;
int board[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

struct point_t {
    int y, x;
    bool operator == (const point_t &b) const {
        return (y == b.y) && (x == b.x);
    }
};

struct node_t {
    point_t a, b;
};

int chebyshev_dist(const point_t &a, const point_t &b) {
    return max(abs(a.y - b.y), abs(a.x - b.x));
}

bool visited[MAXN][MAXN][MAXN][MAXN];
node_t q[MAXN * MAXN * MAXN * MAXN];
int dq = 0, eq = 0;

int bfs(point_t &a_src, point_t &b_src, point_t &a_dst, point_t &b_dst) {
    q[eq++] = {a_src, b_src};
    visited[a_src.y][a_src.x][b_src.y][b_src.x] = true;

    int step = 0;
    while (dq < eq) {
        int qsize = eq - dq;
        for (int k = 0; k < qsize; k++) {
            auto& [a, b] = q[dq++];
            if (a == a_dst && b == b_dst) return step;

            for (int d1 = 0; d1 < 9; d1++) {
                int a_ny = a.y + dy[d1], a_nx = a.x + dx[d1];
                if (!inRange(a_ny, a_nx)) continue;
                if (board[a_ny][a_nx]) continue;

                for (int d2 = 0; d2 < 9; d2++) {
                    int b_ny = b.y + dy[d2], b_nx = b.x + dx[d2];
                    if (!inRange(b_ny, b_nx)) continue;
                    if (board[b_ny][b_nx]) continue;
                    if (chebyshev_dist({a_ny, a_nx}, {b_ny, b_nx}) <= 1) continue;
                    if (visited[a_ny][a_nx][b_ny][b_nx]) continue;

                    visited[a_ny][a_nx][b_ny][b_nx] = true;
                    q[eq++] = { {a_ny, a_nx}, {b_ny, b_nx} };
                }
            }
        }
        step++;
    }
    return -1;
}

int main() {
    scanf("%d", &N);
    point_t a, b, a_home, b_home;
    scanf("%d %d %d %d", &a.y, &a.x, &a_home.y, &a_home.x);
    scanf("%d %d %d %d", &b.y, &b.x, &b_home.y, &b_home.x);
    a.y--, a.x--, a_home.y--, a_home.x--;
    b.y--, b.x--, b_home.y--, b_home.x--;

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%d", &board[y][x]);

    int ret = bfs(a, b, a_home, b_home);
    printf("%d\n", ret);
    return 0;
}