#include <stdio.h>
#include <string.h>

#define debug(x) printf("%s is %d\n", #x, x);
#define debugArr(a, n) do { \
    printf("%s is |", #a); \
    for (int i = 0; i < n; i++) printf("%d|", a[i]); \
    printf("\n"); \
} while(0)
#define swap(type, a, b) do { \
    type t = (a); \
    (a) = (b); \
    (b) = t; \
} while(0)
#define max(a, b) (((a) > (b)) ? (a) : (b))
#define min(a, b) (((a) < (b)) ? (a) : (b))
typedef long long ll;

const int MAXM = 5e5;
const int MAXN = 1e4 + 5;
const int MAXK = 20 + 1;
const int HEAP_SZ = (MAXM * 2) + 5;
const int POOL_SZ = (MAXM * 2) + 5;
const ll INF = 1e17;

struct point_t {
    ll v;
    ll k;
};
struct node_t {
    point_t p;
    ll w;
};

struct priority_queue { // min heap
    node_t arr[HEAP_SZ];
    ll sz = 0;
    void push(node_t node) {
        arr[++sz] = node;
        ll c = sz;
        while (c > 1 && arr[c].w < arr[c/2].w) {
            node_t tmp = arr[c]; arr[c] = arr[c/2]; arr[c/2] = tmp;
            c /= 2;
        }
    }
    node_t pop() {
        node_t ret = arr[1];
        arr[1] = arr[sz--];
        ll p = 1, c = 2;
        while (c <= sz) {
            if (c + 1 <= sz && arr[c + 1].w < arr[c].w) c = c + 1;
            if (arr[p].w <= arr[c].w) break;
            node_t tmp = arr[p]; arr[p] = arr[c]; arr[c] = tmp;
            p = c; c *= 2;
        }
        return ret;
    }
};

ll N, M, K;
ll visited[MAXN][MAXK]; // {N, K}
ll dist[MAXN][MAXK]; // {N, K}

ll head[MAXN];
ll next[POOL_SZ];
point_t val[POOL_SZ];
ll unused = 0;
void insert(ll k, point_t v) {
    unused++;
    val[unused] = v;
    next[unused] = head[k];
    head[k] = unused;
}

priority_queue pq;
ll dijkstra(ll start, ll end) {
    for (ll i = 0; i < MAXN; i++)
        for (ll j = 0; j < MAXK; j++)
            dist[i][j] = INF;

    dist[start][K] = 0;
    pq.push({{start, K}, dist[start][K]});

    while (pq.sz) {
        const auto& [point, _] = pq.pop();
        const auto& [curr, k] = point;

        if (visited[curr][k]) continue;
        visited[curr][k] = true;

        for (ll here = head[curr]; here; here = next[here]) {
            const auto& [next, w] = val[here];
            if (k > 0 && dist[next][k-1] > dist[curr][k]) {
                dist[next][k-1] = dist[curr][k];
                pq.push({{next, k-1}, dist[next][k-1]});
            }
            if (dist[next][k] > dist[curr][k] + w) {
                dist[next][k] = dist[curr][k] + w;
                pq.push({{next, k}, dist[next][k]});
            }
        }
    }

    ll ret = INF;
    for (ll k = 0; k <= K; k++)
        ret = min(ret, dist[end][k]);
    return ret;
}

int main() {
    scanf("%lld %lld %lld", &N, &M, &K);
    for (ll i = 0; i < M; i++) {
        ll u, v, w;
        scanf("%lld %lld %lld", &u, &v, &w);
        insert(u, {v, w});
        insert(v, {u, w});
    }

    ll ret = dijkstra(1, N);
    printf("%lld\n", ret);
    return 0;
}