#include <stdio.h>

const int MAXN = 100 + 5;
const int dy[] = {-1, 0, 1, 0}, dx[] = {0, 1, 0, -1};

int Y, X;
char grid[MAXN][MAXN];
int visited[MAXN][MAXN][4];

struct node_t {
	int y, x, dir, len;
};


bool inRange(int y, int x) {
	return 0 <= y && y < Y && 0 <= x && x < X;
}

node_t q[MAXN * MAXN * MAXN];
int dq, eq;

int bfs(int sy, int sx) {
	for (int d = 0; d < 4; d++) {
		int ny = sy + dy[d], nx = sx + dx[d];
		if (!inRange(ny, nx)) continue;
		if (grid[ny][nx] == 'X') continue;
		q[eq++] = {ny, nx, d, 1};
		visited[ny][nx][d] = true;
	}

	while (dq < eq) {
		node_t curr = q[dq++];
		int y = curr.y, x = curr.x, dir = curr.dir, len = curr.len;

		if (grid[y][x] == 'B') return len;

		for (int d = dir; d < dir + 2; d++) {
			int nd = (d % 4);
			int ny = y + dy[nd], nx = x + dx[nd];
			if (!inRange(ny, nx)) continue;
			if (grid[ny][nx] == 'X') continue;
			if (visited[ny][nx][nd]) continue;
			visited[ny][nx][nd] = true;
			q[eq++] = {ny, nx, nd, len+1};
		}
	}
	return -1;
}


int main(int argc, char** argv) {
	scanf("%d %d", &Y, &X);
	int sy, sx;
	for (int y = 0; y < Y; y++) {
		scanf("%s", &grid[y]);
		for (int x = 0; x < X; x++) {
			if (grid[y][x] == 'A')
				sy = y, sx = x;
		}
	}

	int ret = bfs(sy, sx);
	printf("%d\n", ret);
	return 0;
}