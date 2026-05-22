#include <stdio.h>

#define debug(x) printf("%s is %d\n", #x, x);
#define abs(a) (((a) < 0) ? -(a) : (a))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

const int INF = 1e9;
const int MAXN = 1500 + 5;
const int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

int Y, X;
int P, K;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int manhattan_dist(int ay, int ax, int by, int bx) {
    return abs(ay - by) + abs(ax - bx);
}

struct node_t {
    int y, x;
};
node_t q[MAXN * MAXN];
int eq, dq;

int bfs(int limit) {
    int step = 0;
    while (dq < eq && step < limit) {
        int qsize = eq - dq;
        for (int i = 0; i < qsize; i++) {
            auto [y, x] = q[dq++];
            if (limit == INF && y == Y-1 && x == X-1) return step;

            for (int d = 0; d < 4; d++) {
                int ny = y + dy[d], nx = x + dx[d];
                if (!inRange(ny, nx)) continue;
                if (grid[ny][nx]) continue;
                if (visited[ny][nx]) continue;
                visited[ny][nx] = true;
                q[eq++] = {ny, nx};
            }
        }
        step++;
    }
    return -1;
}


int main() {
    scanf("%d %d", &X, &Y);
    scanf("%d %d", &P, &K);
    for (int i = 0; i < P; i++) {
        int px, py;
        scanf("%d %d", &px, &py);
        py--, px--;
        q[eq++] = {py, px};
        visited[py][px] = true;
    }

    bfs(K);
    eq = dq = 0;

    q[eq++] = {0, 0};
    visited[0][0] = true;
    int ret = bfs(INF);
    printf("%d\n", ret);
    return 0;
}