#include <stdio.h>
#include <string.h>
#define DBG 0
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

typedef long long ll;
const ll MAXN = 5000 + 10;
ll buf[MAXN];

bool comp(ll l, ll r) {
    return l > r; // decreasing
}

void sort(ll arr[], ll s, ll e, bool (*cmp)(ll, ll)) {
    if (s + 1 >= e) return;
    ll m = (s + e)/2;
    sort(arr, s, m, comp);
    sort(arr, m, e, comp);

    ll l = s, r = m, k = 0;
    for (; l < m && r < e; )
        if (cmp(arr[l], arr[r])) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (ll i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

ll solve(ll N, ll arr[]) {
    ll sum = 0;
    while (N > 1) {
        sort(arr, 0, N, comp);
        debugArr(arr, N);
        ll ret = arr[N - 1] + arr[N - 2];
        arr[N - 2] = ret;
        sum += ret;
        N--;
    }

    return sum;
}

int main() {
    ll N; scanf("%lld", &N);
    ll arr[MAXN];
    for (ll  i = 0; i < N; i++)
        scanf("%lld", &arr[i]);

    printf("%lld\n", solve(N, arr));

    return 0;
}