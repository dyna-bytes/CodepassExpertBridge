#include <stdio.h>
typedef long long ll;
const ll INF = 1e17 + 10;
const ll MAXN = 1e5 + 5;
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

int N;
int K;

int get_count(int x) {
    int ret = 0;
    for (int i = 1; i <= N; i++)
        ret += min(x / i, N);
    // printf("x(%d): ret(%d)\n", x, ret);
    return ret;
}

int solve() {
    int l = 0, r = K;
    while (l + 1 < r) {
        int m = (l + r)/2;
        if (get_count(m) >= K) r = m;
        else l = m;
    }
    return r;
}
int main() {
    scanf("%d %d", &N, &K);
    int ret = solve();
    printf("%d\n", ret);
    return 0;
}