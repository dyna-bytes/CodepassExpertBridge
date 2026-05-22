#include <stdio.h>

#define MAXN (1000 + 5)
#define MAXK (30 + 5)
int N, K;

char codes[MAXN][MAXK];
int adj[MAXN][MAXN];
int adj_sz[MAXN];

int hamming_dist(char a[], char b[]) {
    int ret = 0;
    for (int i = 0; i < K; i++)
        if (a[i] != b[i]) ret++;
    return ret;
}

int visited[MAXN];
int q[MAXN];
int eq = 0, dq = 0;
int prv[MAXN];

int bfs(int src, int dst) {
    q[eq++] = src;
    visited[src] = true;

    while (dq < eq) {
        int cur = q[dq++];
        if (cur == dst) {
            int st[MAXN];
            int st_sz = 0;
            for (int i = cur; i != src; i = prv[i])
                st[st_sz++] = i+1;
            st[st_sz++] = src+1;

            for (int i = st_sz-1; i >= 0; i--)
                printf("%d ", st[i]);
            return 0;
        }

        for (int i = 0; i < adj_sz[cur]; i++) {
            int nxt = adj[cur][i];
            if (visited[nxt]) continue;
            visited[nxt] = true;
            prv[nxt] = cur;
            q[eq++] = nxt;
        }
    }

    return -1;
}

int main() {
    scanf("%d %d", &N, &K);
    for (int i = 0; i < N; i++) {
        scanf("%s\n", &codes[i]);
    }
    int src, dst;
    scanf("%d %d", &src, &dst);
    src--;
    dst--;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (hamming_dist(codes[i], codes[j]) == 1) {
                adj[i][adj_sz[i]++] = j;
                adj[j][adj_sz[j]++] = i;
            }
        }
    }

    int ret = bfs(src, dst);
    if (ret) printf("-1");
    return 0;
}