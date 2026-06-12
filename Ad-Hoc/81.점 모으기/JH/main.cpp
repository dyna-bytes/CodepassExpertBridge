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

const int MAXN = 1e4 + 5;
const int MAXM = 1e5 + 5;

int N, M;
int y_points[MAXM];
int x_points[MAXM];

int buf[MAXM];
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

int solve() {
    sort(y_points, 0, M);
    sort(x_points, 0, M);

    int my, mx;
    if (M % 2 == 1) {
        my = y_points[M/2];
        mx = x_points[M/2];
    } else {
        my = (y_points[M/2 - 1] + y_points[M/2])/2;
        mx = (x_points[M/2 - 1] + x_points[M/2])/2;
    }

    int sum = 0;
    for (int i = 0; i < M; i++) {
        sum += abs(y_points[i] - my);
        sum += abs(x_points[i] - mx);
    }
    return sum;
}
int main() {
    scanf("%d %d", &N, &M);
    for (int i = 0; i < M; i++)
        scanf("%d %d", &y_points[i], &x_points[i]);

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}