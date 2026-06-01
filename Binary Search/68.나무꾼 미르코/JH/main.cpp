#include <stdio.h>
typedef long long ll;
const ll INF = 1e17;
const ll MAXN = 1e6 + 5;
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

ll N, M;
ll H[MAXN];

bool check(ll x) {
  ll ret = 0;
  for (int i = 0; i < N; i++) {
    if (x >= H[i]) continue;
    ret += H[i] - x;
  }
  return ret >= M;
}
ll solve() {
  ll l = 0, r = INF;
  while (l + 1 < r) {
    ll m = (l + r)/2;
    if (check(m)) l = m;
    else r = m;
  }
  return l;
}
int main() {
  scanf("%lld %lld", &N, &M);
  for (int i = 0; i < N; i++)
    scanf("%lld", &H[i]);
  ll ret = solve();
  printf("%lld\n", ret);
  return 0;
}