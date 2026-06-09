#include <stdio.h>
#define debug(x) printf("%s is %lld\n", #x, x);
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)
typedef long long ll;
const ll MAXN = 1e5 + 5;

ll N, M;
ll a[MAXN];

bool check(ll x) {
    if (a[0] > x) return false;

    ll sum = a[0];
    ll groups = 1;
    for (int i = 1; i < N; i++) {
        if (a[i] > x) return false;

        if (sum + a[i] > x) {
            sum = a[i];
            groups++;
        } else
            sum += a[i];
    }

    return groups <= M;
}

ll solve() {
    ll l = 0, r = __LONG_LONG_MAX__;
    while (l + 1 < r) {
        ll m = (l + r)/2;
        if (check(m)) r = m;
        else l = m;
    }
    return l + 1;
}

int main() {
    scanf("%lld %lld", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%lld", &a[i]);
    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}