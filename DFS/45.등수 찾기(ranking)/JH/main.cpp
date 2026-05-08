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

const int MAXN = (int)(1e5 + 1);
const int MAXM = (int)(5e5 + 1);

int N;

// 정방향 그래프용
int head[MAXN];      // 각 정점의 첫 번째 간선 번호
int to[MAXM];        // 간선이 가리키는 목적지
int nxt[MAXM];       // 다음 간선의 번호 (연결 리스트 역할)
int edge_cnt;        // 현재까지 추가된 간선 개수

// 역방향 그래프용 (필요하다면 따로 선언)
int ihead[MAXN];
int ito[MAXM];
int inxt[MAXM];
int iedge_cnt;

int visited[MAXN];

void add_edge(int u, int v) {
    edge_cnt++;
    to[edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

void add_reverse_edge(int u, int v) {
    iedge_cnt++;
    ito[iedge_cnt] = v;
    inxt[iedge_cnt] = ihead[u];
    ihead[u] = iedge_cnt;
}

int dfs(int curr, int* head, int* to, int* nxt) {
    int ret = 1;
    for (int i = head[curr]; i != 0; i = nxt[i]) {
        int next = to[i];
        if (visited[next]) continue;
        visited[next] = true;
        ret += dfs(next, head, to, nxt);
    }
    return ret;
}

void solve(int x) {
    memset(visited, 0, sizeof(visited));
    visited[x] = true;
    int smallers = dfs(x, ihead, ito, inxt) - 1;

    memset(visited, 0, sizeof(visited));
    visited[x] = true;
    int largers = dfs(x, head, to, nxt) - 1;

    printf("%d %d", 1 + smallers, N - largers);
}

int main() {
    int M, X;
    scanf("%d %d %d", &N, &M, &X);
    for (int i = 0; i < M; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        add_edge(a, b);
        add_reverse_edge(b, a);
    }

    solve(X);
    return 0;
}