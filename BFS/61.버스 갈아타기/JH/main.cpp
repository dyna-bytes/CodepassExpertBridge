#include <stdio.h>
#include <string.h>
#define DBG 1
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
#define swap(type, a, b) do { \
    type t = a; \
    a = b; \
    b = t; \
} while (0)

const int MAXK = 5e3 + 5;

struct point_t {
    int y, x;
};

bool comp(const point_t& a, const point_t& b) {
    if (a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

struct bus_t {
    point_t begin, end;
    bool operator & (const point_t& point) {
        if (begin.y == end.y) {
            return (begin.y == point.y) && (begin.x <= point.x && point.x <= end.x);
        } else if (begin.x == end.x) {
            return (begin.x == point.x) && (begin.y <= point.y && point.y <= end.y);
        } else
            return false;
    }

    bool operator & (const bus_t& other) {
        bool this_vertical = begin.x == end.x;
        bool other_vertical = other.begin.x == other.end.x;

        if (this_vertical && other_vertical) {
            return (begin.x == other.begin.x) && (begin.y <= other.end.y && end.y >= other.begin.y);
        } else if (!this_vertical && !other_vertical) {
            return (begin.y == other.begin.y) && (begin.x <= other.end.x && end.x >= other.begin.x);
        } else if (this_vertical && !other_vertical) {
            return begin.y <= other.begin.y && other.end.y <= end.y &&
            other.begin.x <= begin.x && end.x <= other.end.x;
        } else if (!this_vertical && other_vertical) {
            return other.begin.y <= begin.y && begin.y <= other.end.y &&
            begin.x <= other.begin.x && other.end.x <= end.x;
        }

        return false;
    }
};

int Y, X;
int K;
bus_t buses[MAXK*2];

int adj[MAXK][MAXK];
int adj_sz[MAXK];

void construct(point_t& start, point_t& dest) {
    for (int b = 1; b <= K; b++) {
        if (buses[b] & start) {
            adj[0][adj_sz[0]++] = b;
            adj[b][adj_sz[b]++] = 0;
        }

        if (buses[b] & dest) {
            adj[K+1][adj_sz[K+1]++] = b;
            adj[b][adj_sz[b]++] = K+1;
        }
    }

    for (int u = 1; u <= K; u++) {
        for (int v = u + 1; v <= K; v++) {
            if (buses[u] & buses[v]) {
                adj[u][adj_sz[u]++] = v;
                adj[v][adj_sz[v]++] = u;
            }
        }
    }
}

int q[MAXK];
int dq, eq;
bool visited[MAXK];
int bfs(int start=0, int end=K+1) {
    q[eq++] = start;
    visited[start] = true;

    int step = 0;
    while (dq < eq) {
        int qsize = eq - dq;
        while (qsize--) {
            int curr = q[dq++];
            if (curr == end) return step - 1;

            for (int i = 0; i < adj_sz[curr]; i++) {
                int next = adj[curr][i];
                if (visited[next]) continue;
                visited[next] = true;
                q[eq++] = next;
            }
        }
        step++;
    }
    return -1;
}

int main() {
    scanf("%d %d", &X, &Y);
    scanf("%d", &K);
    for (int i = 0; i < K; i++) {
        int b, x1, y1, x2, y2;
        scanf("%d %d %d %d %d",
            &b, &x1, &y1, &x2, &y2);
        buses[b] = { {y1, x1}, {y2, x2} };
        if (comp(buses[b].begin, buses[b].end) == false)
            swap(point_t, buses[b].begin, buses[b].end);
    }

    int sx, sy, dx, dy;
    scanf("%d %d %d %d", &sx, &sy, &dx, &dy);
    point_t start = {sy, sx};
    point_t dest = {dy, dx};

    construct(start, dest);
    int ret = bfs();
    printf("%d\n", ret);

    return 0;
}