#include <stdio.h>
#define debug(x) printf("%s is %lld\n", #x, x);
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

typedef long long ll;
const ll MAXN = 2e5 + 5;

ll N, M;
char s[MAXN];
ll a[MAXN];

ll solve() {
    ll ret = 0;
    for (int i = 0; i < N; i++)
        ret += a[i];

    for (int i = 0; i < N; i++) {
        if (s[i] == 'R' && s[(i + 1) % N] == 'L') {
            ll sum = 0;
            for (int j = (i - 1 + N) % N; s[j] == 'R'; j = (j - 1 + N) % N)
                sum += a[j];
            ret -= min(sum, M);

            sum = 0;
            for (int j = (i + 2) % N; s[j] == 'L'; j = (j + 1) % N)
                sum += a[j];
            ret -= min(sum, M);
        }
    }
    return ret;
}

int main() {
    scanf("%lld %lld\n", &N, &M);
    for (int i = 0; i < N; i++)
        scanf("%c", &s[i]);
    for (int i = 0; i < N; i++)
        scanf("%lld", &a[i]);

    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}