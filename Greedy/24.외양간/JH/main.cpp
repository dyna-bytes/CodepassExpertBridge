#include <stdio.h>
#define DBG 0
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

int num_panels;
int num_rooms;
int num_cows;
int num_gaps;

int cows[205];
int gaps[205];

void sort(int s, int e, int arr[]) {
    if (s + 1 >= e) return;
    int m = (s + e)/2;
    sort(s, m, arr);
    sort(m, e, arr);

    int l = s, r = m, k = 0;
    int buf[205];
    for (; l < m && r < e; ) {
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

int solve() {
    if (num_panels >= num_cows) return num_cows;

    sort(0, num_cows, cows);

    int total_len = cows[num_cows - 1] - cows[0] + 1;

    int prev = cows[0];
    for (int i = 1; i < num_cows; i++) {
        int curr = cows[i];
        int gap = curr - prev - 1;
        prev = curr;

        if (gap == 0) continue;
        gaps[num_gaps++] = gap;
    }

    sort(0, num_gaps, gaps);
    debug(total_len);
    for (int i = num_gaps - 1; i >= 0 && num_panels > 1; i--, num_panels--) {
        debug(gaps[i]);
        total_len -= gaps[i];
    }
    return total_len;
}

int main() {
    scanf("%d %d %d \n", &num_panels, &num_rooms, &num_cows);
    for (int i = 0; i < num_cows; i++)
        scanf("%d", &cows[i]);

    int ret = solve();
    printf("%d", ret);
    return 0;
}