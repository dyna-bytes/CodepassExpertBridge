#include <stdio.h>
#define debug(x) printf("%s is %d\n", #x, x);

const int MAXN = 1e2 + 5;
const int HEAP_MAX = MAXN * MAXN * 4;
const int INF = 1e9;
const int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

int N;
int grid[MAXN][MAXN];
int visited[MAXN][MAXN];
int dist[MAXN][MAXN];

bool inRange(int y, int x) {
    return 0 < y && y <= N && 0 < x && x <= N;
}

struct point_t {
    int y, x;
    bool operator == (const point_t& other) {
        return y == other.y && x == other.x;
    }
    bool operator != (const point_t& other) {
        return !(y == other.y && x == other.x);
    }
};

struct node_t {
    point_t p;
    int w;
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

int get_cost(int from, int to) {
    if (from > to) return from - to;
    else if (from < to) return (from - to) * (from - to);
    return 0;
}

priority_queue pq;
point_t prev[MAXN][MAXN];
int dijkstra(int ey, int ex) {
    for (int y = 0; y <= N+1; y++)
        for (int x = 0; x <= N+1; x++)
            dist[y][x] = INF;

    for (int y = 1; y <= N; y++) {
        dist[y][0] = dist[y][N+1] = 0;
        pq.push({{y, 0}, dist[y][0]});
        pq.push({{y, N+1}, dist[y][N+1]});
    }
    for (int x = 1; x <= N; x++) {
        dist[0][x] = dist[N+1][x] = 0;
        pq.push({{0, x}, dist[0][x]});
        pq.push({{N+1, x}, dist[N+1][x]});
    }

    while (!pq.empty()) {
        const auto& [curr, _] = pq.pop();
        const auto& [y, x] = curr;
        if (visited[y][x]) continue;
        visited[y][x] = true;

        if (y == ey && x == ex) return dist[ey][ex];

        for (int d = 0; d < 4; d++) {
            int ny = y + dy[d], nx = x + dx[d];
            if (!inRange(ny, nx)) continue;
            int cost = get_cost(grid[y][x], grid[ny][nx]);
            if (dist[ny][nx] <= dist[y][x] + cost) continue;
            dist[ny][nx] = dist[y][x] + cost;
            pq.push({{ny, nx}, dist[ny][nx]});
            prev[ny][nx] = {y, x};
        }
    }

    return -1;
}
int main() {
    scanf("%d", &N);
    int ey, ex;
    scanf("%d %d", &ey, &ex);
    for (int y = 1; y <= N; y++)
        for (int x = 1; x <= N; x++)
            scanf("%d", &grid[y][x]);

    int ret = dijkstra(ey, ex);
    printf("%d\n", ret);
    return 0;
}