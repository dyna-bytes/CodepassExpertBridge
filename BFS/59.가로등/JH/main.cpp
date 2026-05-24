#include <stdio.h>
#define debug(x) printf("%s is %d\n", #x, x);
#define abs(a) (((a) < 0) ? -(a) : (a))
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) > (y)) ? (x) : (y))

typedef long long ll;
const ll INF = 1e18 + 7;
const ll MAXN = 3e5 + 5;
const ll MAXK = 5e5 + 5;

#define HASH_SIZE (4000037)
struct hash_t {
    ll keys[HASH_SIZE] = {};
    ll vals[HASH_SIZE] = {};

    ll hash(ll k) {
        return ((k % HASH_SIZE) * 29) % HASH_SIZE;
    }

    void init() {
        for (int i = 0; i < HASH_SIZE; i++) {
            keys[i] = -1;
            vals[i] = false;
        }
    }

    void put(ll k, ll v) {
        ll h = hash(k);
        while (keys[h] != -1 && keys[h] != k)
            h = (h + 1) % HASH_SIZE;

        keys[h] = k;
        vals[h] = v;
    }

    ll get(ll k) {
        ll h = hash(k);
        while (keys[h] != -1) {
            if (keys[h] == k) return vals[h];
            h = (h + 1) % HASH_SIZE;
        }

        return false;
    }
};

struct node_t {
    ll x;
    ll dist;
};

ll L, N, K;
ll lights[MAXN];

bool inRange(ll x) {
    return 0 <= x && x <= L;
}

hash_t visited;
node_t q[MAXN + MAXK * 2] = {};
int eq = 0, dq = 0;

void bfs() {
    visited.init();

    for (int i = 0; i < N; i++) {
        q[eq++] = {lights[i], 0};
        visited.put(lights[i], true);
    }

    ll ret[MAXK];
    int ret_sz = 0;
    while (dq < eq && ret_sz < K) {
        auto [x, dist] = q[dq++];
        ret[ret_sz++] = dist;

        if (inRange(x+1) && !visited.get(x+1)) {
            visited.put(x+1, true);
            q[eq++] = {x+1, dist+1};
        }

        if (inRange(x-1) && !visited.get(x-1)) {
            visited.put(x-1, true);
            q[eq++] = {x-1, dist+1};
        }
    }

    for (int i = 0; i < ret_sz; i++)
        printf("%lld\n", ret[i]);
}

int main() {
    scanf("%lld %lld %lld", &L, &N, &K);

    for (int i = 0; i < N; i++)
        scanf("%lld", &lights[i]);

    bfs();

    return 0;
}