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

const ll INF = 1e17;
const int MAXN = 500 + 5;
const int MAXP = 800 + 5;
const int MAXC = 1450 + 5;
const int HEAP_MAX = MAXP * MAXP;

struct node_t {
    ll v;
    ll w;
};

struct priority_queue {
    node_t arr[HEAP_MAX];
    int sz = 0;

    void push(node_t node) {
        arr[++sz] = node;
        int c = sz;
        while (c > 1 && arr[c].w < arr[c/2].w) {
            node_t tmp = arr[c];
            arr[c] = arr[c/2];
            arr[c/2] = tmp;
            c /= 2;
        }
    }
    node_t pop() {
        node_t ret = arr[1];
        arr[1] = arr[sz--];

        int p = 1, c = 2;
        while (c <= sz) {
            if (c+1 <= sz && arr[c+1].w < arr[c].w) c++;
            if (arr[p].w <= arr[c].w) break;
            node_t tmp = arr[p];
            arr[p] = arr[c];
            arr[c] = tmp;
            p = c; c *= 2;
        }
        return ret;
    }
    bool empty() { return sz == 0; }
};

int N, P, C;

ll adj[MAXP][MAXP];
int students[MAXN];

ll dist[MAXP];
int visited[MAXP];

void dijkstra(int start) {
    for (int i = 0; i < MAXP; i++) visited[i] = 0;
    for (int i = 0; i < MAXP; i++) dist[i] = INF;

    priority_queue pq;
    dist[start] = 0;
    pq.push({start, dist[start]});

    while (!pq.empty()) {
        auto [curr, _] = pq.pop();
        if (visited[curr]) continue;
        visited[curr] = true;

        for (int next = 1; next <= P; next++) {
            ll weight = adj[curr][next];
            if (weight == 0) continue;
            if (dist[next] <= dist[curr] + weight) continue;
            dist[next] = dist[curr] + weight;

            pq.push({next, dist[next]});
        }
    }
}

int solve() {
    ll ret = INF;
    for (int start = 1; start <= P; start++) {
        dijkstra(start);

        ll sum = 0;
        for (int i = 0; i < N; i++) {
            sum += dist[students[i]];
        }
        ret = min(ret, sum);
    }
    return ret;
}

int main() {
    scanf("%d %d %d", &N, &P, &C);
    for (int i = 0; i < C; i++) {
        int u, v, cost;
        scanf("%d %d %d", &u, &v, &cost);
        adj[u][v] = adj[v][u] = cost;
    }
    for (int i = 0; i < N; i++) {
        scanf("%d", &students[i]);
    }

    ll ret = solve();
    printf("%lld\n", ret);
    return 0;
}