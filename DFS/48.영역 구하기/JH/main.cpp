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
const int dy[] = { -1, 0, 1, 0 }, dx[] = { 0, 1, 0, -1 };

int Y, X;
int board[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < Y && 0 <= x && x < X;
}

int dfs(int y, int x) {
    int ret = 1;

    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (board[ny][nx]) continue;
        if (visited[ny][nx]) continue;
        visited[ny][nx] = true;
        ret += dfs(ny, nx);
    }
    return ret;
}

void sort(int arr[], int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(arr, s, m);
    sort(arr, m, e);

    int l = s, r = m, k = 0;
    int buf[MAXN * MAXN] = {};
    for (; l < m && r < e; ) {
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }
    for (; l < m; ) buf[k++] = arr[l++];
    for (; r < e; ) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

void solve() {
    int areas[MAXN * MAXN] = {};
    int areas_sz = 0;

    debugArr2D(board, Y, X);
    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            if (board[y][x]) continue;
            if (visited[y][x]) continue;
            visited[y][x] = true;
            int area = dfs(y, x);
            areas[areas_sz++] = area;
        }
    }

    sort(areas, 0, areas_sz);
    printf("%d\n", areas_sz);
    for (int i = 0; i < areas_sz; i++)
        printf("%d ", areas[i]);
}

int main() {
    int K;

    scanf("%d %d %d", &Y, &X, &K);
    for (int i = 0; i < K; i++) {
        int lx, ly, rx, ry;
        scanf("%d %d %d %d", &lx, &ly, &rx, &ry);
        for (int y = ly; y < ry; y++)
            for (int x = lx; x < rx; x++)
                board[y][x] = (i + 1);
    }

    solve();

    return 0;
}