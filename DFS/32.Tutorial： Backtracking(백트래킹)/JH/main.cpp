#include <stdio.h>
#include <string.h>
#define DBG 1
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif

int MAXN = 10;

int PI(int n, int k, int stack[], int sp) {
    if (k == 0) {
        for (int i = 0; i < sp; i++)
            printf("%d ", stack[i]);
        printf("\n");
        return 1;
    }

    int ret = 0;
    for (int i = 1; i <= n; i++) {
        stack[sp++] = i;
        ret += PI(n, k-1, stack, sp);
        sp--;
    }
    return ret;
}

int P(int n, int k, int stack[], int sp, int visited[]) {
    if (k == 0) {
        for (int i = 0; i < sp; i++)
            printf("%d ", stack[i]);
        printf("\n");
        return 1;
    }

    int ret = 0;
    for (int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        stack[sp++] = i;
        ret += P(n, k-1, stack, sp, visited);
        sp--;
        visited[i] = false;
    }
    return ret;
}

int H(int n, int k, int stack[], int sp, int prev) {
    if (k == 0) {
        for (int i = 0; i < sp; i++)
            printf("%d ", stack[i]);
        printf("\n");
        return 1;
    }

    int ret = 0;
    for (int i = prev; i <= n; i++) {
        stack[sp++] = i;
        ret += H(n, k-1, stack, sp, i);
        sp--;
    }
    return ret;
}

int C(int n, int k, int stack[], int sp, int prev) {
    if (k == 0) {
        for (int i = 0; i < sp; i++)
            printf("%d ", stack[i]);
        printf("\n");
        return 1;
    }

    int ret = 0;
    for (int i = prev + 1; i <= n; i++) {
        stack[sp++] = i;
        ret += C(n, k-1, stack, sp, i);
        sp--;
    }
    return ret;
}

int main() {
    int T, N, K; // N 이랑 K 바꿔 사용
    scanf("%d %d %d", &T, &K, &N);

    int ret;
    int buf[MAXN] = {};
    int visited[MAXN] = {};

    if (T == 1) {
        ret = PI(N, K, buf, 0);
    } else if (T == 2) {
        ret = P(N, K, buf, 0, visited);
    } else if (T == 3) {
        ret = H(N, K, buf, 0, 1);
    } else if (T == 4) {
        ret = C(N, K, buf, 0, 0);
    }

    printf("%d\n", ret);

    return 0;
}