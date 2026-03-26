#include <stdio.h>
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);

const int N = 19;
const int B = 1;
const int W = 2;
                // UR R RD D
const int dy[] = {-1, 0, 1, 1};
const int dx[] = {1, 1, 1, 0};

int board[N][N];
bool inRange(int y, int x) {
    return 0 <= y && y < N && 0 <= x && x < N;
}

int check(int y, int x, int dir, int depth=1) {
    if (depth == 1) {
        int py = y - dy[dir], px = x - dx[dir];
        if (inRange(py, px) && (board[py][px] == board[y][x]))
            return 0;
    }

    int ny = y + dy[dir], nx = x + dx[dir];
    if (!inRange(ny, nx)) return depth;
    if (board[ny][nx] == board[y][x])
        return check(ny, nx, dir, depth + 1);

    return depth;
}

void solve() {
    int chk = 0;
    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            for (int dir = 0; dir < 4; dir++)
                if (board[y][x] && (check(y, x, dir) == 5)) {
                    printf("%d\n", board[y][x]);
                    printf("%d %d", y + 1, x + 1);
                    return;
                }
        }
    }

    printf("0");
}

int main() {
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++)
            scanf("%d", &board[y][x]);

    solve();
    return 0;
}