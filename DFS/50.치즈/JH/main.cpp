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

const int MAXN = 100 + 5;
const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

int Y, X;
int board[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

void dfs(int y, int x) {

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (board[ny][nx]) {
            board[ny][nx] = 2;
            continue;
        }
        if (visited[ny][nx]) continue;
        visited[ny][nx] = true;
        dfs(ny, nx);
    }
}

int solve() {
    int day = 0;
    int cnt = 0;
    int ans = 0;
    while (true) {
        memset(visited, 0, sizeof(visited));

        for (int y = 0; y < Y-1; y++) {
            visited[y][0] = true;
            dfs(y, 0);
        }
        for (int x = 0; x < X-1; x++) {
            visited[Y-1][x] = true;
            dfs(Y-1, x);
        }
        for (int y = 0; y < Y-1; y++) {
            visited[Y-1-y][0] = true;
            dfs(Y-y-1, 0);
        }
        for (int x = 0; x < X-1; x++) {
            visited[0][X-1-x] = true;
            dfs(0, x);
        }

        cnt = 0;
        for (int y = 0; y < Y; y++) {
            for (int x = 0; x < X; x++) {
                if (board[y][x] == 2) {
                    board[y][x] = 0;
                    cnt++;
                }
            }
        }

        if (cnt == 0) break;
        ans = cnt;
        day++;
    }

    printf("%d\n", day);
    printf("%d\n", ans);
    return ans;
}
int main() {
    scanf("%d %d", &Y, &X);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &board[y][x]);

    solve();
    return 0;
}