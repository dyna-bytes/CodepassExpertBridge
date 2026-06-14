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

const int MAXN = 1000'000 + 5;

int buf[MAXN];
void sort(int arr[], int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(arr, s, m);
    sort(arr, m, e);

    int l = s, r = m, k = 0;
    while (l < m && r < e) {
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }
    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];
    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}


int L, N;
int ants[MAXN];

int get_mintime() {
    double mid = L/2.0;
    double closest = L;
    for (int i = 0; i < N; i++) {
        double dist = abs(mid - ants[i]);
        closest = min(closest, dist);
    }
    return mid - closest;
}
int get_maxtime() {
    double mid = L/2.0;
    double farthest = 0;
    for (int i = 0; i < N; i++) {
        double dist = abs(mid - ants[i]);
        farthest = max(farthest, dist);
    }
    return mid + farthest;
}
void solve() {
    sort(ants, 0, N);
    printf("%d ", get_mintime());
    printf("%d ", get_maxtime());
}

int main() {
    scanf("%d %d", &L, &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &ants[i]);
    solve();
    return 0;
}