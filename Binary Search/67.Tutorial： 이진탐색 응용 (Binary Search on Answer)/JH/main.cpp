#include <stdio.h>
#include <string.h>

#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while(0)
#define swap(type, a, b) do { \
    type t = (a); \
    (a) = (b); \
    (b) = t; \
} while(0)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
typedef long long ll;
const ll MAXN = 2e5 + 5;

ll N, T;
ll a[MAXN];
ll max_a;
ll check(ll x) {
    ll sum = 0;
    for (int i = 0; i < N; i++)
        sum += min(x, a[i]);
    return sum >= T;
}

ll solve() {
    ll l = 0, r = max_a;
    while (l + 1 < r) {
        ll m = (l + r)/2;
        if (check(m)) r = m;
        else l = m;
    }
    return l + 1;
}
int main() {
    scanf("%lld %lld", &N, &T);
    for (int i = 0; i < N; i++) {
        scanf("%lld", &a[i]);
        max_a = max(max_a, a[i]);
    }
    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}