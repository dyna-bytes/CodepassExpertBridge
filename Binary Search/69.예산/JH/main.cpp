#include <stdio.h>
typedef long long ll;
const ll INF = 1e17;
const ll MAXN = 1e6 + 5;
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)
int N;
ll arr[MAXN];
ll max_budget;

bool check(ll x) {
    ll ret = 0;
    for (int i = 0; i < N; i++)
        ret += min(arr[i], x);
    return ret <= max_budget;
}

ll solve() {
    ll l = 0, r = 0;
    for (int i = 0; i < N; i++) r = max(r, arr[i]);
    r++;

    while (l + 1 < r) {
        ll m = (l + r) / 2;
        if (check(m)) l = m;
        else r = m;
    }
    return l;
}


int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%lld", &arr[i]);
    scanf("%lld", &max_budget);
    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}