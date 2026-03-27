#include <stdio.h>
#include <functional>
using namespace std;
#define DBG 0
#if DBG
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#else
#define debug(x)
#endif
const int MAXN = 5;
                // UR R RD D
const int dy[4] = {-1, 0, 1, 1};
const int dx[4] = {1, 1, 1, 0};
typedef struct {
    int y;
    int x;
} point_t;

bool inRange(int y, int x) {
    return 0 <= y && y < MAXN && 0 <= x && x < MAXN;
}

int solve(int board[MAXN][MAXN], point_t map[MAXN * MAXN], int orders[MAXN * MAXN]) {
    function<int(int, int, int)> checkline = [&](int y, int x, int dir) {
        if (!inRange(y, x)) return 0;
        if (board[y][x]) return 0;
        int ny = y + dy[dir], nx = x + dx[dir];
        return 1 + checkline(ny, nx, dir);
    };

    auto bingo = [&]() {
        int ret = 0;
        int chk;
        for (int y = 0; y < MAXN; y++)
            for (int x = 0; x < MAXN; x++) {
                if (board[y][x]) continue;

                for (int dir = 0; dir < 4; dir++){
                    if ((chk = checkline(y, x, dir)) == MAXN)
                        ret++;
                    debug(chk);
                }
            }

        return ret >= 3;
    };

    for (int k = 0; k < MAXN * MAXN; k++) {
        auto [y, x] = map[orders[k]];
        board[y][x] = 0;

#if DBG
        for (int y = 0; y < MAXN; y++) {
            for (int x = 0; x < MAXN; x++)
                printf("%d ", board[y][x]);
            printf("\n");
        }
#endif

        if (bingo()) return k + 1;
    }

    return 0;
}

int main() {
    int board[MAXN][MAXN];
    point_t map[MAXN * MAXN + 1];
    for (int y = 0; y < 5; y++)
        for (int x = 0; x < 5; x++) {
            scanf("%d", &board[y][x]);
            map[board[y][x]] = { y, x };
        }

    int orders[MAXN * MAXN];
    for (int i = 0; i < MAXN * MAXN; i++)
        scanf("%d", &orders[i]);

    printf("%d\n", solve(board, map, orders));
    return 0;
}