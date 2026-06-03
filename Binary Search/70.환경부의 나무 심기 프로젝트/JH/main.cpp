#include <stdio.h>
const int INF = 1e9 + 10;
const int MAXN = 2e5 + 5;
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

int N;
int K;
int x_points[MAXN];

bool check(int min_dist) {
    int trees = 1;
    int prev_x = x_points[0];
    for (int i = 1; i < N; i++) {
        int dist = x_points[i] - prev_x;
        if (dist >= min_dist) {
            trees++;
            prev_x = x_points[i];
        }
    }

    return trees >= K;
}
int solve() {
    int l = 0, r = INF;
    while (l + 1 < r) {
        int m = (l + r)/2;
        if (check(m)) l = m;
        else r = m;
    }
    return l;
}

int buf[MAXN];
void sort(int arr[], int s, int e) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(arr, s, m);
    sort(arr, m, e);

    int l = s, r = m, k = 0;
    for (; l < m && r < e; )
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}
int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++)
        scanf("%d", &x_points[i]);

    sort(x_points, 0, N);

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}