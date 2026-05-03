#include <stdio.h>
#include <string.h>
#define DBG 0
#if DBG
#define debug(x) printf("%s is %d\n", #x, x);
#else
#define debug(x)
#endif

#define min(a, b) ((a) < (b) ? (a) : (b))
#define max(a, b) ((a) > (b) ? (a) : (b))
#define abs(x) ((x) < 0 ? -(x) : (x))

const int INF = 1e9 + 7;
const int MAXN = 50 + 5;
const int MAXK = 13 + 5;

enum {
    SPACE,
    HOUSE,
    SHOP
};

struct point_t {
    int y, x;
};

int N;
int K;
int num_shops;
int num_houses;
point_t shops[MAXK];
point_t houses[MAXN*MAXN];


int st[(int)1e5]; // SUM[k=0~13] { C(13,k) } = 2^13 = 8192
int sp;
int res[(int)1e5][MAXK];
int rp;

void C(int n, int k, int prev) {
    if (k == 0) {
        for (int i = 0; i < K; i++)
            res[rp][i] = st[i];
        rp++;
        return;
    }

    for (int curr = prev + 1; curr < n; curr++) {
        st[sp++] = curr;
        C(n, k-1, curr);
        sp--;
    }
}

int get_min_dist_sum(int num_houses, point_t houses[], int num_shops, point_t shops[]) {
    int ret = 0;
    for (int i = 0; i < num_houses; i++) {
        auto [hy, hx] = houses[i];
        int min_dist = INF;

        for (int j = 0; j < num_shops; j++) {
            auto [sy, sx] = shops[j];

            int dist = abs(hy - sy) + abs(hx - sx);
            min_dist = min(min_dist, dist);
        }

        ret += min_dist;
    }
    return ret;
}

int solve() {
    C(num_shops, K, -1);

    int ret = INF;
    debug(rp);
    for (int i = 0; i < rp; i++) {
        point_t selected_shops[MAXK] = {};

        for (int j = 0; j < K; j++) {
            int shop_id = res[i][j];
            selected_shops[j] = shops[shop_id];
        }

        int sum = get_min_dist_sum(num_houses, houses, K, selected_shops);

        debug(sum);
        ret = min(ret, sum);
    }
    return ret;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int y = 0; y < N; y++)
        for (int x = 0; x < N; x++) {
            int inp;
            scanf("%d", &inp);
            if (inp == SHOP) {
                shops[num_shops++] = {y, x};
            } else if (inp == HOUSE) {
                houses[num_houses++] = {y, x};
            }
        }

    int ret = solve();
    printf("%d\n", ret);

    return 0;
}