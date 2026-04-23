#include <stdio.h>
#define debug(x) printf("%s is %d\n", #x, x);
#define min(a, b) (a < b) ? (a) : (b)
typedef long long ll;
const int INF = 1e9 + 5;
const int MAXN = 1e5 + 5;

int N, K;
ll breads[MAXN];
ll buf[MAXN];
ll pref[MAXN];

void sort(int s, int e, ll arr[]) {
    if (s + 1 >= e) return;
    int m = (s + e) / 2;
    sort(s, m, arr);
    sort(m, e, arr);

    int l = s, r = m, k = 0;
    while (l < m && r < e)
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[s + i] = buf[i];
}

ll solve() {
    sort(0, N, breads);

    for (int i = 0; i < N; i++)
    pref[i+1] = pref[i] + breads[i];

    ll sum = 0;
    for (int i = 0; i < K; i++)
        sum += ((2*i - K + 1) * breads[i]);

    ll ret = sum;
    for (int i = 0; i + K < N; i++) {
        sum -= (-K + 1) * breads[i];
        sum -= 2 * (pref[i + K] - pref[i + 1]);
        sum += (K - 1) * breads[i + K];

        ret = min(ret, sum);
    }

    return ret;
}

int main() {
    scanf("%d", &N);
    scanf("%d", &K);

    for (int i = 0; i < N; i++) {
        scanf("%lld", &breads[i]);
    }

    printf("%lld\n", solve());

    return 0;
}