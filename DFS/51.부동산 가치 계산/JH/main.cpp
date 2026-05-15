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
#define swap(a, b) do { \
    __typeof__(a) tmp = (a); \
    (a) = (b); \
    (b) = tmp; \
} while (0)

typedef long long ll;
const int MAXN = 30;
const int D_MAXN = MAXN * MAXN;
const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

int N;
int board[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}
ll dfs(int y, int x, int type, int id) {
    ll ret = 1;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (board[ny][nx] != type) continue;
        if (visited[ny][nx] != -1) continue;
        visited[ny][nx] = id;
        ret += dfs(ny, nx, type, id);
    }
    return ret;
}

struct land_t {
    ll area;
    ll type;
};

land_t lands[D_MAXN];
int lands_sz;

int adj[D_MAXN][D_MAXN];
ll connects[D_MAXN][D_MAXN];

ll calc(int u, int sz) {
    if (u >= sz) return 0;
    ll ret = 0;
    for (int v = u + 1; v < sz; v++) {
        if (adj[u][v] == false) continue;
        ret += (lands[u].area + lands[v].area)
            * lands[u].type * lands[v].type * (connects[u][v] / 2);
    }
    ret += calc(u + 1, sz);
    return ret;
}

ll do_calc() {
    memset(visited, -1, sizeof(visited));
    memset(lands, 0, sizeof(lands));
    lands_sz = 0;
    memset(adj, 0, sizeof(adj));
    memset(connects, 0, sizeof(connects));

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (visited[y][x] != -1) continue;
            visited[y][x] = lands_sz;
            lands[lands_sz].area = dfs(y, x, board[y][x], lands_sz);
            lands[lands_sz].type = board[y][x];
            lands_sz++;
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                int u = visited[ny][nx];
                int v = visited[y][x];

                if (u != v) {
                    adj[u][v] = adj[v][u] = true;
                    connects[u][v]++;
                    connects[v][u]++;
                }
            }
        }
    }

    return calc(0, lands_sz);
}

void rotate(int sy, int sx, int ey, int ex) { // CW
    int h = ey - sy;
    int w = ex - sx;
    if (h != w) return;

    for (int y = 0; y < h; y++)
        for (int x = y + 1; x < w; x++)
            swap(board[sy + y][sx + x], board[sy + x][sx + y]);

    for (int y = 0; y < h; y++)
        for (int x = 0; x < w/2; x++)
            swap(board[sy + y][sx + x], board[sy + y][sx + (w-1-x)]);
}

void rotate_cross(int my, int mx) {
    int buf[MAXN][MAXN] = {};
    memcpy(buf, board, sizeof(board));

    for (int y = 0; y < N; y++)
        for (int x = y + 1; x < N; x++)
            swap(buf[y][x], buf[x][y]);

    for (int x = 0; x < N; x++)
        for (int y = 0; y < N/2; y++)
            swap(buf[y][x], buf[N - y - 1][x]);

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (y == my || x == mx)
                board[y][x] = buf[y][x];
}

void do_rotate() {
    rotate_cross(N/2, N/2);
    rotate(0, 0, N/2, N/2);
    rotate(0, N/2 + 1, N/2, N);
    rotate(N/2 + 1, 0, N, N/2);
    rotate(N/2 + 1, N/2 + 1, N, N);
    debugArr2D(board, N, N);
}

ll solve() {
    ll ret = do_calc();
    for (int step = 0; step < 3; step++) {
        do_rotate();
        ret += do_calc();
    }
    return ret;
}

int main() {
    scanf("%d", &N);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%d", &board[y][x]);

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}