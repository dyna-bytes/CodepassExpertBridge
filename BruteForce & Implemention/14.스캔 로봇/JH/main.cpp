#include <stdio.h>
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
const int MAXN = 50 + 1;
const int dy[4] = {-1, 0, 1, 0};
const int dx[4] = {0, -1, 0, 1};

typedef struct {
    int y, x;
    int dir;
} point_t;

int Y, X;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int solve(int sy, int sx, int sdir) {
    point_t q[MAXN * MAXN];
    int eq = 0, dq = 0;

    int ret = 0;
    q[eq++] = { sy, sx, sdir };
    visited[sy][sx] = true;
    ret++;

    while (dq < eq) {
        auto [y, x, dir] = q[dq++];
        debug(y);
        debug(x);
        debug(dir);

        if (!visited[y][x]) {
            visited[y][x] = true;
            ret++;
        }

        bool suc = false;
        for (int d = 1; d < 5; d++) {
            int nd = (dir + d) % 4;
            int ny = y + dy[nd], nx = x + dx[nd];
            if (!inRange(ny, nx)) continue;
            if (grid[ny][nx]) continue;
            if (visited[ny][nx]) continue;

            q[eq++] = { ny, nx, nd };
            suc = true;
            break;
        }

        if (!suc) {
            int nd = (dir + 2) % 4;
            int ny = y + dy[nd], nx = x + dx[nd];
            if (!inRange(ny, nx)) return ret;
            if (grid[ny][nx]) return ret;
            q[eq++] = { ny, nx, dir };
        }
    }

    return ret;
}

int main() {
    scanf("%d %d", &Y, &X);

    int sy, sx, sdir;
    scanf("%d %d %d", &sy, &sx, &sdir);

    if (sdir == 1) sdir = 3;
    else if (sdir == 3) sdir = 1;

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &grid[y][x]);

    printf("%d\n", solve(sy, sx, sdir));
    return 0;
}