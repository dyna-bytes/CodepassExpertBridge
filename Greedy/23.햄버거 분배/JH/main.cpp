#include <stdio.h>
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while (0)
#else
#define debug(x)
#define debugArr(a, n)
#endif
#define abs(x) (x) < 0 ? -(x) : (x)
const int MAXN = 2e5 + 10;

int N, K;

int H = 0, P = 0;
int hamburgers[MAXN];
int people[MAXN];

int solve() {
    int cnt = 0;
    for (int h = 0, p = 0; h < H && p < P; h++, p++) {
        while (p < P && hamburgers[h] - people[p] > K)
            p++;
        while (h < H && people[p] - hamburgers[h] > K)
            h++;

        cnt++;
        debug(people[p]);
        debug(hamburgers[h]);
    }
    return cnt;
}

int main() {
    scanf("%d %d \n", &N, &K);
    for (int i = 0; i < N; i++) {
        char c; scanf("%c", &c);
        if (c == 'H') hamburgers[H++] = i;
        else if (c == 'P') people[P++] = i;
    }
    debugArr(people, P);
    debugArr(hamburgers, H);

    printf("%d\n", solve());
    return 0;
}