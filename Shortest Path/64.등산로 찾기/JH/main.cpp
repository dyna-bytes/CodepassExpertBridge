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

const int INF = 1e9;
const int MAXN = 1e3 + 5;
const int MAXM = 1e4 + 5;

struct edge_t {
    int to, weight;
};

int N;
int M;
int X;

int unused;
int head[MAXN];
int next[MAXM];
edge_t val[MAXM];

void insert(int k, edge_t v) {
    unused++;
    val[unused] = v;
    next[unused] = head[k];
    head[k] = unused;
}

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

int visited[MAXN];
int dist[MAXN];
int dijkstra(int start, int end) {
    for (int i = 0; i < MAXN; i++) visited[i] = 0;
    for (int i = 0; i < MAXN; i++) dist[i] = INF;

    priority_queue<edge_t, MAXM, comp> pq;
    dist[start] = 0;
    pq.push({start, dist[start]});

    while (pq.sz) {
        auto [cur, _] = pq.pop();
        if (visited[cur]) continue;
        visited[cur] = true;

        if (cur == end)
            return dist[end];

        for (int node = head[cur]; node; node = next[node]) {
            auto& [nxt, weight] = val[node];
            if (dist[nxt] <= dist[cur] + weight) continue;
            dist[nxt] = dist[cur] + weight;
            pq.push({nxt, dist[nxt]});
        }
    }
    return -1;
}

int solve() {
    int ans[MAXN] = {};
    dijkstra(X, -1);
    for (int i = 1; i <= N; i++)
        ans[i] = dist[i];

    for (int i = 1; i <= N; i++) {
        int cost = dijkstra(i, X);
        ans[i] += cost;
    }

    int ret = 0;
    for (int i = 1; i <= N; i++)
        ret = max(ret, ans[i]);
    return ret;
}

int main() {
    scanf("%d %d %d", &N, &M, &X);
    for (int i = 0; i < M; i++) {
        int from, to, dist;
        scanf("%d %d %d", &from, &to, &dist);
        insert(from, {to, dist});
    }

    int ret = solve();
    printf("%d\n", ret);
    return 0;
}