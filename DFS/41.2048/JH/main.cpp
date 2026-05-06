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

const int MAXN = 21;
int N;
int arr[MAXN][MAXN];

void move(int& from, int& to) {
    to = from;
    from = 0;
}

// horizontal: left, vertical: up
void move_forward(int row[]) {
    int s = 0; // segment start
    int e = 0; // next segment end

    for (; s < N - 1; s++) {
        e = s;
        while (++e < N && row[s] == 0)
            move(row[e], row[s]);

        e = s + 1;
        while (++e < N && row[s + 1] == 0)
            move(row[e], row[s + 1]);

        if (row[s] == row[s + 1]) {
            row[s] *= 2;
            row[s + 1] = 0;
        }
    }
}

// horizontal: right, vertical: down
void move_backward(int row[]) {
    int s = N - 1;
    int e = N - 1;

    for (int s = N - 1, e = N - 1; s > 0; s--) {
        e = s;
        while (--e >= 0 && row[s] == 0)
            move(row[e], row[s]);

        e = s - 1;
        while (--e >= 0 && row[s - 1] == 0)
            move(row[e], row[s - 1]);

        if (row[s] == row[s - 1]) {
            row[s] *= 2;
            row[s - 1] = 0;
        }
    }
}

void do_pull(int board[MAXN][MAXN], int to_vertical) {
    int inner_buf[MAXN][MAXN];

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (to_vertical)
                inner_buf[x][y] = board[y][x];
            else
                inner_buf[y][x] = board[y][x];

    for (int y = 0; y < N; y++)
        move_forward(inner_buf[y]);

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (to_vertical)
                board[x][y] = inner_buf[y][x];
            else
                board[y][x] = inner_buf[y][x];
}

void do_push(int board[MAXN][MAXN], int to_vertical) {
    int inner_buf[MAXN][MAXN];

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (to_vertical)
                inner_buf[x][y] = board[y][x];
            else
                inner_buf[y][x] = board[y][x];

    for (int y = 0; y < N; y++)
        move_backward(inner_buf[y]);

    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            if (to_vertical)
                board[x][y] = inner_buf[y][x];
            else
                board[y][x] = inner_buf[y][x];
}

int get_max(int board[MAXN][MAXN]) {
    int ret = 0;
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            ret = max(ret, board[y][x]);
    return ret;
}

int dfs(int cnt, int board[MAXN][MAXN]) {
    if (cnt >= 5) {
        debugArr2D(board, N, N);
        return get_max(board);
    }

    int ret = 0;
    int buf[MAXN][MAXN];
    for (int d = 0; d < 4; d++) {
        for (int y = 0; y < N; y++)
            for (int x = 0; x < N; x++)
                buf[y][x] = board[y][x];

        if (d < 2)  do_pull(buf, d % 2);
        else        do_push(buf, d % 2);
        int result = dfs(cnt + 1, buf);
        ret = max(ret, result);
    }

    return ret;
}

int main() {
    scanf("%d", &N);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%d", &arr[y][x]);

    int ret = dfs(0, arr);
    printf("%d", ret);

    return 0;
}