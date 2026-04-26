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

const int MAXN = 500 + 10;

int N;
int meetings[MAXN][3];
int buf[MAXN][3];

bool comp(int l[3], int r[3]) {
    if (l[2] == r[2]) return l[1] < r[1];
    return l[2] < r[2];
}

void sort(int arr[][3], int s, int e, bool (*cmp)(int[3], int[3])) {
    if (s + 1 >= e) return;
    int m = (s + e) / 2;
    sort(arr, s, m, cmp);
    sort(arr, m, e, cmp);

    int l = s, r = m, k = 0;
    for (; l < m && r < e; ) {
        if (cmp(arr[l], arr[r])) {
            memcpy(buf[k], arr[l], sizeof(arr[l]));
            k++, l++;
        } else {
            memcpy(buf[k], arr[r], sizeof(arr[r]));
            k++, r++;
        }
    }

    while (l < m) {
        memcpy(buf[k], arr[l], sizeof(arr[l]));
        k++, l++;
    }
    while (r < e) {
        memcpy(buf[k], arr[r], sizeof(arr[r]));
        k++, r++;
    }

    for (int i = 0; i < k; i++)
        memcpy(arr[i + s], buf[i], sizeof(buf[i]));
}

void solve() {
    sort(meetings, 0, N, comp);
    int cnt = 0;
    int prev_e = 0;
    int ans[MAXN];

    debugArr2D(meetings, N, 3);

    for (int i = 0; i < N; i++) {
        int id = meetings[i][0];
        int s = meetings[i][1];
        int e = meetings[i][2];

        debug(id);
        debug(s);
        debug(e);

        if (prev_e > s) continue;
        prev_e = e;
        ans[cnt++] = id;
    }

    printf("%d\n", cnt);
    for (int i = 0; i < cnt; i++)
        printf("%d ", ans[i]);
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
        scanf("%d %d %d",
            &meetings[i][0], &meetings[i][1], &meetings[i][2]);
    }
    solve();
    return 0;
}