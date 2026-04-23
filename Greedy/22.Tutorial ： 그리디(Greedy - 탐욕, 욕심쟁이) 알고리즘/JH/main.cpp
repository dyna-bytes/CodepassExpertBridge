#include <stdio.h>
#define min(a, b) ((a) < (b) ? (a) : (b))

int weights[5] = {1, 2, 4, 8, 16};

int solve(int nums[], int N) {
    int ret = 0;

    for (int i = 4; i >= 0 && N > 0; i--) {
        int r = min(N / weights[i], nums[i]);
        N -= r * weights[i];

        ret += r;
    }

    if (N > 0) return -1;
    return ret;
}

int main() {
    int nums[5];
    int N;
    for (int i = 0; i < 5; i++)
        scanf("%d", &nums[i]);
    scanf("%d", &N);

    int ret = solve(nums, N);
    if (ret == -1) printf("impossible\n");
    printf("%d", ret);
    return 0;
}