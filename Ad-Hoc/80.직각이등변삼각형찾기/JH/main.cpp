#include <stdio.h>
#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while (0)
#define debugArr2d(a, Y, X) do { \
    printf("%s is \n", #a); \
    for (int y = 0; y < Y; y++) debugArr(a[y], X); \
    printf("\n"); \
} while (0)
#define swap(t, x, y) do { \
    t tmp = x; \
    x = y; \
    y = tmp; \
} while (0)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

const int MAXN = 10 + 5;
const int N = 10;
int grid[MAXN][MAXN];
int cnt;

void rotate(int __grid[MAXN][MAXN]) { // clockwise
    int buf[MAXN][MAXN] = {};
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            buf[x][y] = __grid[y][x];

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            __grid[y][x] = buf[y][N - 1 - x];
}

struct point_t {
    int y, x;
};

struct triangle_t {
    point_t p[3];
};

/**
00000
0*000
0**00
0***0
00000
*/
bool isType1(int sy, int sx, triangle_t& ret) {
    if (sy > 0 && grid[sy - 1][sx]) return false;

    int ey = sy;
    while (ey < N && grid[ey][sx]) ey++;
    --ey;

    int h = ey - sy;
    if (h < 2) return false;

    int ex = sx + h;
    if (ex >= N) return false;

    int __cnt = 0;
    for (int y = sy; y <= ey; y++) {
        int w = y - sy;
        int left = sx;
        int right = sx + w;

        for (int x = left; x <= right; x++) {
            if (grid[y][x]) __cnt++;
            else return false;
        }

        if (right + 1 < N && grid[y][right + 1]) return false;
    }

    ret.p[0] = (point_t){sy, sx};
    ret.p[1] = (point_t){ey, sx};
    ret.p[2] = (point_t){ey, ex};

    return cnt == __cnt;
}


/**
00000
0*000
0**00
0*000
00000
*/
bool isType2(int sy, int sx, triangle_t& ret) {
    int ey = sy;
    while (ey < N && grid[ey][sx]) ey++;
    --ey;

    int h = ey - sy;
    if (h < 2) return false;

    if (h % 2 != 0) return false;

    int half = h / 2;
    int mid = sy + half;

    if (sx - half < 0) return false;

    int __cnt = 0;
    for (int y = sy; y <= ey; y++) {
        int d = abs(y - mid);
        int left = sx - (half - d);
        int right = sx;
        if (left < 0 || right >= N) return false;

        for (int x = left; x <= right; x++) {
            if (grid[y][x]) __cnt++;
            else return false;
        }
    }

    ret.p[0] = {sy, sx};
    ret.p[1] = {mid, sx - half};
    ret.p[2] = {ey, sx};

    return cnt == __cnt;
}


point_t rotateBack(int y, int x, int iter) {
    point_t p;
    switch (iter) {
        case 0: p.y = y; p.x = x; break;
        case 1: p.y = N - 1 - x; p.x = y; break;
        case 2: p.y = N - 1 - y; p.x = N - 1 - x; break;
        case 3: p.y = x; p.x = N - 1 - y; break;
    }
    return p;
}

void sortPoints(point_t p[3]) {
    for (int i = 0; i < 2; i++) {
        for (int j = i + 1; j < 3; j++) {
            if (p[i].y > p[j].y || (p[i].y == p[j].y && p[i].x > p[j].x)) {
                swap(point_t, p[i], p[j]);
            }
        }
    }
}

void print_result(triangle_t& tri, int iter) {
    for (int i = 0; i < 3; i++)
        tri.p[i] = rotateBack(tri.p[i].y, tri.p[i].x, iter);

    sortPoints(tri.p);

    for (int i = 0; i < 3; i++)
        printf("%d %d\n", tri.p[i].y + 1, tri.p[i].x + 1);
}

void solve() {
    for (int iter = 0; iter < 4; iter++) {
        for (int sy = 0; sy < N; sy++) {
            for (int sx = 0; sx < N; sx++) {
                if (grid[sy][sx]) {
                    triangle_t tri;
                    if (isType1(sy, sx, tri)) {
                        print_result(tri, iter);
                        return;
                    }

                    if (isType2(sy, sx, tri)) {
                        print_result(tri, iter);
                        return;
                    }
                }
            }
        }
        // debugArr2d(grid, N, N);

        rotate(grid);
    }

    printf("0\n");
}

int main() {
    for (int y = 0; y < N; y++) {
        char buf[MAXN];
        scanf("%s", buf);

        for (int x = 0; x < N; x++) {
            grid[y][x] = buf[x] - '0';

            if (grid[y][x] == 1) cnt++;
        }
    }

    solve();
    // debug(cnt);
    return 0;
}