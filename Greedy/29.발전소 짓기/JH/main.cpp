#include <stdio.h>
#include <string.h>
#define debug(x) printf("%s is %d\n", #x, x)

const int MAXN = 1e5 + 10;
int arr[MAXN];

int solve(int n, int k, int cities[]) {
    int range = 0; // [0, range)
    int ret = 0;

    for (int i = 0; i < n; i++) {
        if (cities[i] == 0) continue;

        int j = i;
        int prev_j = -1;

        for (j = i; j < n; j++) {
            if (cities[j] == 0) continue;
            int left = j - k + 1; // [left, right)
            int right = j + k;

            if (left > range) {
                j = prev_j;
                break;
            }

            prev_j = j;
        }

        if (prev_j == -1) return -1;
        range = j + k;
        ret++;
        i = j;
    }
    return ret;
}

int main() {
    int N, K;
    scanf("%d %d\n", &N, &K);

    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    printf("%d\n", solve(N, K, arr));

    return 0;
}