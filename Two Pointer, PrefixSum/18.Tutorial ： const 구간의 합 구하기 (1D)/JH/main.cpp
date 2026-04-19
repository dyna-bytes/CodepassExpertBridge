#include <stdio.h>
#define DBG 1
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

typedef long long ll;
const int MAXN = 1e6 + 10;

int N;
int A[MAXN];
int Q;
int queries[MAXN][2];
ll pref[MAXN];

void solve() {
    for (int i = 0; i < N; i++)
        pref[i + 1] = pref[i] + A[i];

    for (int i = 0; i < Q; i++) {
        int s = queries[i][0], e = queries[i][1];
        printf("%lld\n", pref[e] - pref[s - 1]);
    }
}

int main() {
    scanf("%d", &N);

    for (int i = 0; i < N; i++)
        scanf("%d", &A[i]);

    scanf("%d", &Q);

    for (int i = 0; i < Q; i++)
        scanf("%d %d", &queries[i][0], &queries[i][1]);

    solve();

    return 0;
}