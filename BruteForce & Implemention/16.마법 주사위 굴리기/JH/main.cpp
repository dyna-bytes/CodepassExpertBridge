#include <stdio.h>
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

            //   S  E  W  N
const int dy[] = {1, 0, 0, -1};
const int dx[] = {0, 1, -1, 0};
const int MAXN = 20 + 1;
const int MAXK = 1000 + 1;

enum directions {
    SOUTH,
    EAST,
    WEST,
    NORTH
};

enum faces {
    FRONT,
    HEAD,
    LEFT,
    BACK,
    TAIL,
    RIGHT
};

int Y, X;
int K;
bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int grid[MAXN][MAXN] = {};
int cmds[MAXK] = {};
int cube[6] = {}; // [F, H, L, B, T, R]
// 0[F] <=> 3[B], 1[H] <=> 4[T], 2[L] <=> 5[R]
int face = HEAD;
int bottom = TAIL;

int leftrightroll_p = 0;
int leftrightroll[] = {HEAD, LEFT, TAIL, RIGHT};
int updownroll_p = 0;
int updownroll[] = {HEAD, BACK, TAIL, FRONT};

void solve(int y, int x) {
    for (int k = 0; k < K; k++) {
        int d = cmds[k];
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        y = ny, x = nx;

        if (d == EAST) {
            int buffer = cube[leftrightroll[0]];

            for (int i = 0; i < 3; i++)
                cube[leftrightroll[i]] = cube[leftrightroll[i+1]];
            cube[leftrightroll[3]] = buffer;
        } else if (d == WEST) {
            int buffer = cube[leftrightroll[3]];

            for (int i = 3; i > 0; i--)
                cube[leftrightroll[i]] = cube[leftrightroll[i-1]];
            cube[leftrightroll[0]] = buffer;
        } else if (d == SOUTH) {
            int buffer = cube[updownroll[0]];

            for (int i = 0; i < 3; i++)
                cube[updownroll[i]] = cube[updownroll[i+1]];
            cube[updownroll[3]] = buffer;
        } else if (d == NORTH) {
            int buffer = cube[updownroll[3]];

            for (int i = 3; i > 0; i--)
                cube[updownroll[i]] = cube[updownroll[i-1]];
            cube[updownroll[0]] = buffer;
        }

        if (grid[y][x]) {
            cube[bottom] = grid[y][x];
            grid[y][x] = 0;
        } else {
            grid[y][x] = cube[bottom];
        }
        debugArr(cube, 6);
        debugArr2D(grid, Y, X);

        printf("%d\n", cube[face]);
    }
}

int main() {
    int sy, sx;
    scanf("%d %d %d %d %d\n",
        &Y, &X, &sy, &sx, &K);

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &grid[y][x]);

    for (int k = 0; k < K; k++) {
        scanf("%d", &cmds[k]);
        cmds[k] %= 4;
    }

    solve(sy, sx);
    return 0;
}