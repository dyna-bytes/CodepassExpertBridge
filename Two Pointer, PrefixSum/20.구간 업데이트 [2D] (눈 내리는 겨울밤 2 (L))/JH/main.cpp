#include <stdio.h>
const int MAXN = 1e3 + 5;
const int MAXQ = 1e6 + 5;

int N;
int Q;
int pref[MAXN][MAXN];
int grid[MAXN][MAXN];
int queries[MAXQ][5];

void solve() {
    for (int i = 0; i < Q; i++) {
        int sy = queries[i][0];
        int sx = queries[i][1];
        int ey = queries[i][2];
        int ex = queries[i][3];
        int val = queries[i][4];

        pref[sy - 1][sx - 1] += val;
        pref[sy - 1][ex] += -val;
        pref[ey][sx - 1] += -val;
        pref[ey][ex] += val;
    }

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            grid[y][x + 1] = grid[y][x] + pref[y][x];
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 1; x <= N; x++) {
            grid[y + 1][x] += grid[y][x];
        }
    }

    for (int y = 0; y < N; y++) {
        for (int x = 1; x <= N; x++)
            printf("%d ", grid[y][x]);
        printf("\n");
    }
}

int main() {
    scanf("%d %d", &N, &Q);
    for (int i = 0; i < Q; i++) {
        scanf("%d %d %d %d %d",
            &queries[i][0], &queries[i][1],
            &queries[i][2], &queries[i][3],
            &queries[i][4]);
    }
    solve();

    return 0;
}