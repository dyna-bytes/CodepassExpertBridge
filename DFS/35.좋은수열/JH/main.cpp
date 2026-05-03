#include <stdio.h>
#include <string.h>
#define DBG 1
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

const int INF = 1e9 + 7;
const int MAXN = 85;

int N;

int st[MAXN];
int sp;

int dfs(int i, int st[]) {
    if (i >= N) {
        int ret = 0;
        for (int sp = 0; sp < N; sp++) {
            printf("%d", st[sp]);
        }
        return true;
    }

    auto is_good = [&](int i) {
        if (i == 0) return true;

        int ret = false;
        for (int k = 1; k <= (i+1)/2; k++) {
            int s = i + 1 - 2*k;
            int m = i + 1 - k;
            int e = i + 1;
            bool bad = true;

            for (int l = s, r = m; l < m && r < e; l++, r++)
                if (st[l] != st[r]) {
                    bad = false;
                    break;
                }

            ret += bad;
        }
        return !ret;
    };

    for (int curr = 1; curr <= 3; curr++) {
        st[sp++] = curr;
        if (is_good(i)) {
            if (dfs(i+1, st))
                return true;
        }
        st[sp--] = 0;
    }
    return false;
}


int main() {
    scanf("%d", &N);

    dfs(0, st);
    return 0;
}