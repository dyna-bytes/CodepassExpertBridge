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

const int INF = 1e9;
const int MAXN = 100 + 5;

int N;

int adj[MAXN][MAXN];
int dist[MAXN];
int visited[MAXN];
int prv[MAXN];

struct edge_t {
    int to, weight;
};

struct comp {
    bool operator()(const edge_t& a, const edge_t& b) const {
        return a.weight > b.weight; // max heap
    }
};

template <typename T, int HEAP_SZ, typename Compare>
struct priority_queue {
    int sz = 0;
    T arr[HEAP_SZ];
    Compare cmp;

    void heapify_down() {
        int curr = 1;

        while (curr * 2 <= sz) {
            int left = curr * 2;
            int right = curr * 2 + 1;

            int larger_child = left;
            if (right <= sz && cmp(arr[left], arr[right]))
                larger_child = right;

            if (cmp(arr[curr], arr[larger_child])) {
                swap(T, arr[curr], arr[larger_child]);
                curr = larger_child;
            } else {
                break;
            }
        }
    }

    void heapify_up() {
        int curr = sz;

        while (curr > 1) {
            int parent = curr / 2;
            if (cmp(arr[parent], arr[curr])) {
                swap(T, arr[parent], arr[curr]);
                curr = parent;
            } else {
                break;
            }
        }
    }

    T pop() {
        T ret = arr[1];
        arr[1] = arr[sz--];
        if (sz > 0)
            heapify_down();
        return ret;
    }

    void push(const T &val) {
        arr[++sz] = val;
        heapify_up();
    }
};

int bfs(int src, int dst) {
    priority_queue<edge_t, MAXN * MAXN, comp> pq;

    for (int i = 0; i < MAXN; i++)
        dist[i] = INF;
    memset(prv, -1, sizeof(prv));
    dist[src] = 0;

    pq.push({src, dist[src]});

    while (pq.sz) {
        auto [cur, _] = pq.pop();
        if (visited[cur]) continue;
        visited[cur] = true;

        if (cur == dst) {
            printf("%d\n", dist[dst]);
            int st[MAXN] = {};
            int st_sz = 0;
            for (int here = dst; here != -1; here = prv[here])
                st[st_sz++] = here;

            for (int i = st_sz - 1; i >= 0; i--)
                printf("%d ", st[i] + 1);
            return dist[dst];
        }

        for (int nxt = 0; nxt < N; nxt++) {
            int weight = adj[cur][nxt];
            if (weight == 0) continue;
            if (dist[nxt] <= dist[cur] + weight) continue;
            dist[nxt] = dist[cur] + weight;
            prv[nxt] = cur;
            pq.push({nxt, dist[nxt]});
        }
    }
    return -1;
}

int main() {
    int dst;
    scanf("%d %d", &N, &dst);
    dst--;

    for (int u = 0; u < N; u++)
        for (int v = 0; v < N; v++)
            scanf("%d", &adj[u][v]);

    bfs(0, dst);
    return 0;
}