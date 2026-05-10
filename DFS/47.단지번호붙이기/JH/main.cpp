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

const int MAXN = 30;
const int dy[4] = {-1, 0, 1, 0}, dx[4] = {0, 1, 0, -1};

int N;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int dfs(int y, int x) {
    int ret = 1;
    for (int d = 0; d < 4; d++) {
        int ny = y + dy[d], nx = x + dx[d];
        if (!inRange(ny, nx)) continue;
        if (grid[ny][nx] == 0) continue;
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

    int buf[MAXN * MAXN] = {};
    int l = s, r = m, k = 0;
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
    int stack[MAXN * MAXN] = {};
    int stack_sz = 0;
    debugArr2D(grid, N, N);

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            if (grid[y][x] == 0) continue;
            if (visited[y][x]) continue;
            visited[y][x] = true;
            stack[stack_sz++] = dfs(y, x);
        }
    }

    sort(stack, 0, stack_sz);
    printf("%d\n", stack_sz);
    for (int i = 0; i < stack_sz; i++)
        printf("%d\n", stack[i]);
}
int main() {
    scanf("%d", &N);
    for (int y = 0; y < N; y++) {
        char buf[MAXN];
        scanf("%s", buf);
        for (int x = 0; x < N; x++)
            grid[y][x] = buf[x] - '0';
    }
    solve();
    return 0;
}