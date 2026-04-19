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
} while (0)j
#else
#define debug(x)
#define debugArr(A, N)
#define debugArr2D(AA, Y, X)
#endif
#define abs(a) ((a < 0) ? -(a) : (a))
const int MAXN = 1e5+1;
const int INF = 1e14;
typedef long long ll;

void solve(int N, ll liquids[]) {
    int s = 0, e = N-1;

    ll min_sum = INF;
    ll ans[2];

    while (s < e) {
        ll sum = liquids[s] + liquids[e];

        if (abs(min_sum) > abs(sum)) {
            min_sum = sum;
            ans[0] = liquids[s];
            ans[1] = liquids[e];
        }

        if (sum < 0) s++;
        else e--;
    }

    printf("%lld %lld\n", ans[0], ans[1]);
}

int main() {
    int N; scanf("%d", &N);
    ll liquids[MAXN];
    for (int i = 0; i < N; i++)
        scanf("%lld", &liquids[i]);

    solve(N, liquids);
    return 0;
}