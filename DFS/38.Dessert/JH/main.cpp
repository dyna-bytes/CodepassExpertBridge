#include <stdio.h>
#include <string.h>
#define DBG 0
#if DBG
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x);
#define debugArr(A, N) do { \
    printf("[%s](%d) %s is |", __func__, __LINE__, #A); \
    for (int i = 0; i < N; i++) printf("%d|", A[i]); \
    printf("\n"); \
} while (0)
#define debugArr2D(AA, Y, X) do { \
    printf("[%s](%d) %s is \n", __func__, __LINE__, #AA); \
    for (int y = 0; y < Y; y++) debugArr(AA[y], X); \
    printf("\n"); \
} while (0)
#else
#define debug(x)
#define debugArr(A, N)
#define debugArr2D(AA, Y, X)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

const int INF = 1e9 + 7;
const int MAXN = 20;

int N;
char arr[MAXN];
int ans_cnt;

int dfs(int sp, char st[]) {
    if (sp >= N) {
        int cow = 1;
        int curr_num = cow++;

        int n = 0;
        int cows[MAXN] = {};

        int m = 0;
        char ops[MAXN] = {};

        for (int i = 0; i < sp; i++) {
            if (st[i] == '+' || st[i] == '-') {
                cows[n++] = curr_num;
                ops[m++] = st[i];
                curr_num = cow++;
            } else if (st[i] == '.') {
                int mul = (cow >= 10) ? 100 : 10;
                curr_num = curr_num * mul + cow++;
            }
        }

        cows[n++] = curr_num;

        int ret = cows[0];
        for (int i = 1, j = 0; i < n && j < m; i++, j++) {
            if (ops[j] == '+')
                ret += cows[i];
            else if (ops[j] == '-')
                ret -= cows[i];
        }

        if (ret) return false;
        else if (ans_cnt++ >= 20) return true;

        debug(cow);
        debugArr(cows, n);
        debugArr(ops, m);
#if DBG
        printf("%d ", cows[0]);
        for (int i = 1, j = 0; i < n && j < m; i++, j++) {
            printf("%c %d ", ops[j], cows[i]);
        }
        printf("\n");
#endif
        printf("%d ", 1);
        for (int i = 0; i < sp; i++) {
            printf("%c %d ", st[i], i + 2);
        }
        printf("\n");

        return true;
    }

    int ret = 0;
    st[sp] = '+';
    ret += dfs(sp + 1, st);

    st[sp] = '-';
    ret += dfs(sp + 1, st);

    st[sp] = '.';
    ret += dfs(sp + 1, st);

    return ret;
}

int main() {
    scanf("%d", &N);
    N--;

    int ret = dfs(0, arr);
    printf("%d", ret);
    return 0;
}