#include <stdio.h>
#define DBG 1
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif
#define max(a, b) ((a) > (b) ? (a) : (b))
typedef long long ll;
const ll MAXN = 2e5 + 5;
const ll MOD = 4e4;

struct fire_t {
    ll a, b;
};

fire_t arr[MAXN], buf[MAXN];

bool comp(fire_t* l, fire_t* r) {
    if (l->b == 0 && r->b == 0) return l->a > r->a;
    else if (l->b == 0) return true; // return l
    else if (r->b == 0) return false; // return r
    return (double)(l->a) / (l->b) > (double)(r->a) / (r->b);
}

void sort(fire_t arr[], int s, int e, bool (*cmp)(fire_t*, fire_t*)) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(arr, s, m, cmp);
    sort(arr, m, e, cmp);

    int l = s, r = m, k = 0;
    for (; l < m && r < e; ) {
        if (cmp(&arr[l], &arr[r])) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }
    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

ll solve(int n, fire_t fires[]) {
    sort(fires, 0, n, comp);
    ll ret = 0;
    for (int i = 0; i < n; i++) {
        ret = (ret + fires[i].a * ret + fires[i].b) % MOD;
    }
    return ret;
}

int main() {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d", &arr[i].a, &arr[i].b);
    }

    int ret = solve(N, arr);
    printf("%d\n", ret);

    return 0;
}