#include <stdio.h>
#include <cstring>
using namespace std;
#define swap(a, b) {int tmp=a; a=b; b=tmp;}
#define debug(x) printf("[%s](%d) %s is %d\n", __func__, __LINE__, #x, x)

const int MAXN = 1000 + 1;

void rotate(char arr[MAXN][MAXN], int& Y, int& X) {
    int buf[MAXN][MAXN] = { 0, };

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            buf[x][Y - y - 1] = arr[y][x];

    swap(Y, X);
    for (int y = 0; y < Y; y++)
        memset(arr[y], 0, sizeof(arr[y]));

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            arr[y][x] = buf[y][x];
}

void flip(char arr[MAXN][MAXN], int Y, int X) {
    int buf[MAXN][MAXN] = { 0, };

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            buf[y][X - x - 1] = arr[y][x];

    for (int y = 0; y < Y; y++)
        for (int x = 0; x < X; x++)
            arr[y][x] = buf[y][x];
}

void print(char arr[MAXN][MAXN], int Y, int X) {
    printf("%d %d\n", X, Y);
    for (int y = 0; y < Y; y++) {
        printf("%s\n", arr[y]);
    }
}

int main() {
    int Y, X;
    char arr[MAXN][MAXN] = { 0, };
    int C;

    scanf("%d %d", &X, &Y);
    for (int y = 0; y < Y; y++)
        scanf("%s", arr[y]);
    scanf("%d", &C);

    if (C < 3)
        for (int i = 0; i <= C; i++)
            rotate(arr, Y, X);

    if (C == 3) {
        rotate(arr, Y, X);
        flip(arr, Y, X);
        for (int i = 0; i < 3; i++)
            rotate(arr, Y, X);
    }

    if (C == 4)
        flip(arr, Y, X);

    print(arr, Y, X);

    return 0;
}