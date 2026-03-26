#include <stdio.h>
using namespace std;
#define min(a, b) ((a < b) ? (a) : (b))
#define max(a, b) ((a > b) ? (a) : (b))
#define debug(x) printf("%s is %d\n", #x, x);
const int MAXN = 1000 + 1;

int solve(int N, int mountains[MAXN]) {
    int mn = 100, mx = 0;
    for (int i = 0; i < N; i++) {
        mn = min(mn, mountains[i]);
        mx = max(mx, mountains[i]);
    }

    auto getcost = [&](int baseline, int ceiling) {
        int cost = 0;
        for (int i = 0; i < N; i++) {
            if (baseline > mountains[i])
                cost += (baseline - mountains[i]) * (baseline - mountains[i]);
            else if (ceiling < mountains[i])
                cost += (ceiling - mountains[i]) * (ceiling - mountains[i]);
        }
        return cost;
    };

    int mincost = 0x7FFFFFFF;
    for (int L = mn; L <= max(mx - 17, mn); L++) {
        mincost = min(mincost, getcost(L, L + 17));
    }
    return mincost;
}

int main() {
    int N;
    scanf("%d", &N);
    int mountains[MAXN];
    for (int i = 0; i < N; i++)
        scanf("%d", &mountains[i]);

    printf("%d", solve(N, mountains));
    return 0;
}