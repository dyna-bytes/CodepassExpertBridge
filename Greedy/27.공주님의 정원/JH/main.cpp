#include <stdio.h>
#include <string.h>
#define DBG 1
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while (0)
#define debugArr2D(aa, Y, X) do { \
    printf("[%s](%d) %s is \n", __func__, __LINE__, #aa); \
    for (int y = 0; y < Y; y++) debugArr(aa[y], X); \
    printf("\n"); \
} while (0)
#else
#define debug(x)
#define debugArr(a, n)
#define debugArr2D(aa, Y, X)
#endif
#define max(a, b) (a) > (b) ? (a) : (b)

const int MAXN = 1e5 + 10;
const int months[13] = {
    0, 31, 28, 31, 30, 31, 30, 31,
    31, 30, 31, 30, 31
};

int N;
int flowers[MAXN][4];
int end_days[MAXN];

int to_days(int mm, int dd) {
    int days = 0;
    for (int i = 1; i < mm; i++)
        days += months[i];
    return days + dd;
}

/**
 * @brief Two Pointer, Greedy
 * 꽃이 03월 01일부터 11월 30일 까지 끊임없이 계속 피어있으려면
 * 결국 모든 꽃의 구간을 겹쳤을 때, 하나의 "연속된 구간"이 나와야 한다.
 * 따라서, 현재까지 만들 수 있는 최대의 구간 내에서
 * 가장 오른쪽으로 갈 수 있는 새로운 구간의 상한을 찾고
 * 이를 다시 현재 구간의 상한으로 삼아 다시 하나의 연속된 구간을 만들어내면 된다.
 * (이 구간은 과거부터 연속된 하나의 구간이며, 현재까지 만들 수 있는 최대 길이의 구간이다.)
 */
int solve(int N, int flowers[][4]) {
    for (int i = 0; i < N; i++) {
        int s = to_days(flowers[i][0], flowers[i][1]);
        int e = to_days(flowers[i][2], flowers[i][3]);
        end_days[s] = max(end_days[s], e);
    }

    int ret = 0;
    int s = to_days(01, 01);
    int e = to_days(03, 01);

    // 구간의 우측 끝이 11월 30일을 넘는다면 종료
    while (e <= to_days(11, 30)) {
        int max_e = 0;

        // 구간 [s, e]에서 가장 지는 날이 늦는 꽃을 찾음
        for (; s <= e; s++)
            max_e = max(max_e, end_days[s]);

        // 더 이상 우향하는 연속되는 구간을 만들어내지 못할 경우
        if (max_e < e) return 0;
        // 구간의 우측 끝 갱신
        e = max_e;
        ret++;
    }
    return ret;
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        for (int j = 0; j < 4; j++)
            scanf("%d", &flowers[i][j]);

    int ret = solve(N, flowers);
    printf("%d\n", ret);

    return 0;
}