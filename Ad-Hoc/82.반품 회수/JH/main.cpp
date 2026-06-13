#include <stdio.h>
#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while (0)
#define debugArr2d(a, Y, X) do { \
    printf("%s is \n", #a); \
    for (int y = 0; y < Y; y++) debugArr(a[y], X); \
    printf("\n"); \
} while (0)
#define swap(t, x, y) do { \
    t tmp = x; \
    x = y; \
    y = tmp; \
} while (0)
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

const int MAXN = 3e3 + 5;

int buf[MAXN];
bool comp(int arr[], int l, int r) {
    return arr[l] < arr[r];
}
void sort(int key[], int arr[], int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(key, arr, s, m);
    sort(key, arr, m, e);

    int l = s, r = m, k = 0;
    while (l < m && r < e) {
        if (key[arr[l]] < key[arr[r]]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }
    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];
    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

int N;
int X[MAXN];
int T[MAXN];

int solve() {
    int order[MAXN] = {};
    for (int i = 0; i < N; i++)
        order[i] = i;
    sort(X, order, 0, N);

    int t = max(X[order[N-1]], T[order[N-1]]);

    for (int k = N-2; k >= 0; k--) {
        int i = order[k];
        int j = order[k+1];
        t += abs(X[i] - X[j]);
        t = max(t, T[i]);
    }

    t += abs(X[order[0]] - 0);
    return t;
}
int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &X[i]);

    for (int i = 0; i < N; i++)
        scanf("%d", &T[i]);
    int ret = solve();
    printf("%d\n", ret);
    return 0;
}