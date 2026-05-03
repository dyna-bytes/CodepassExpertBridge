#include <stdio.h>
#include <string.h>
#define DBG 1
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif

const int MAXN = 10;

void f(int n, int m, int stack[], int sp) {
    if (n == 0) {
        if (m != 0) return;

        for (int i = 0; i < sp; i++)
            printf("%d ", stack[i]);
        printf("\n");
        return;
    }

    if (m == 0) return;

    for (int i = 1; i <= 6; i++) {
        if (i > m) continue;
        stack[sp++] = i;
        f(n-1, m-i, stack, sp);
        sp--;
    }
}

int main() {
    int N, M;
    scanf("%d %d", &N, &M);
    int buf[MAXN] = {};
    f(N, M, buf, 0);
    return 0;
}