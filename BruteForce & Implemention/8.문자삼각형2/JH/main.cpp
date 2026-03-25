#include <stdio.h>
#include <cstring>
using namespace std;

const int MAXN = 100;
int N;
int Y, X;
int A[MAXN][MAXN];

void solve() {
    memset(A, ' ', sizeof(A));

    int k = 0;
    for (int x = X-1; x >= 0; x--)
        for (int y = x; y < N - x; y++) {
            A[y][x] = 'A' + k;
            k = (k + 1) % 26;
        }

    for (int y = 0; y < Y; y++) {
        for (int x = 0; x < X; x++) {
            printf("%c", A[y][x]);
            if (x != X - 1)
                printf(" ");
        }
        printf("\n");
    }
}

int main() {
    scanf("%d", &N);
    if ((N <= 0) || (N >= 100) || (N % 2 == 0)) {
        printf("INPUT ERROR\n");
        return 0;
    }
    Y = N;
    X = N/2 + 1;
    solve();

    return 0;
}