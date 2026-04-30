#include <stdio.h>
#define DBG 0
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif
#define max(a, b) ((a) > (b) ? (a) : (b))
const int MAXN = 1e3 + 5;

struct job_t {
    int id;
    double unit_cost;
};

job_t arr[MAXN];
job_t buf[MAXN];

bool decreasing(job_t *a, job_t *b) {
    if (a->unit_cost == b->unit_cost) return a->id < b->id;
    return a->unit_cost > b->unit_cost;
}

void sort(job_t arr[], int s, int e, bool (*cmp)(job_t *a, job_t *b)) {
    if (s + 1 >= e) return;

    int m = (s + e)/2;
    sort(arr, s, m, cmp);
    sort(arr, m, e, cmp);

    int l = s, r = m, k = 0;
    for (; l < m && r < e; ) {
        if (cmp(&arr[l], &arr[r])) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];
    }

    while (l < m) buf[k++] = arr[l++];
    while (r < e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[i + s] = buf[i];
}

void solve(int n, job_t jobs[]) {
    sort(jobs, 0, n, decreasing);

    for (int i = 0; i < n; i++)
        printf("%d ", jobs[i].id);
}
int main() {
    int N;
    scanf("%d\n", &N);
    for (int i = 0; i < N; i++) {
        int time, cost;
        scanf("%d %d", &time, &cost);
        arr[i].id = i + 1;
        arr[i].unit_cost = cost / (double)time; // cost per time
    }

    solve(N, arr);
    return 0;
}