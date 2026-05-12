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

const int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

const int MAXN = 30 + 5;
int Y, X;
int fst[MAXN][MAXN];
int snd[MAXN][MAXN];

int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

void dfs(int y, int x, int grp, int clr) {

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (fst[ny][nx] != clr) continue;
        if (visited[ny][nx]) continue;
        visited[ny][nx] = grp;
        dfs(ny, nx, grp, clr);
    }
}

int cmp(int y, int x, int grp, int clr) {
    if (snd[y][x] != clr) return true;

    int ret = 0;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (visited[ny][nx] != grp) continue;
        visited[ny][nx] = 0;
        ret += cmp(ny, nx, grp, clr);
    }
    return ret;
}

int solve() {
    int group = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (visited[y][x]) continue;
            visited[y][x] = ++group;
            dfs(y, x, group, fst[y][x]);
        }
    }

    debugArr2D(visited, Y, X);

    int diff_cnt = 0;
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (visited[y][x] == 0) continue;
            int grp = visited[y][x];
            visited[y][x] = 0;
            int ret = cmp(y, x, grp, snd[y][x]);
            debug(ret);
            if (ret) return false;

            if (fst[y][x] != snd[y][x]) diff_cnt++;
            debug(diff_cnt);
            if (diff_cnt >= 2) return false;
        }
    }
    return true;
}

int main() {
    scanf("%d %d", &Y, &X);

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &fst[y][x]);
    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            scanf("%d", &snd[y][x]);

    int ret = solve();
    if (ret) printf("YES\n");
    else printf("NO\n");
    return 0;
}