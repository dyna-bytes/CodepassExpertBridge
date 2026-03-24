#include <iostream>
using namespace std;

const int MAXN = 30 + 1;
int N, M;

int triangle[MAXN][MAXN];
void print();
void fill() {
    triangle[0][0] = 1;
    for (int y = 1; y < N; y++) {
        triangle[y][0] = triangle[y][y] = 1;
        for (int x = 1; x < y; x++) {
            triangle[y][x] = triangle[y-1][x-1] + triangle[y-1][x];
        }
    }
}

void print() {
    if (M == 1) {
        for (int y = 0; y < N; y++) {
            for (int x = 0; x <= y; x++) {
                printf("%d ", triangle[y][x]);
            }
            printf("\n");
        }
    }
    else if (M == 2) {
        for (int y = N-1; y >= 0; y--) {
            for (int k = 0; k < N - y - 1; k++)
                printf(" ");
            for (int x = 0; x <= y; x++) {
                printf("%d ", triangle[y][x]);
            }
            printf("\n");
        }
    }
    else if (M == 3) {
        for (int x = N-1; x >= 0; x--) {
            for (int y = N-1; y >= x; y--)
                printf("%d ", triangle[y][x]);
            printf("\n");
        }
    }
}
int main() {
    scanf("%d", &N);
    scanf("%d", &M);
    fill();
    print();


    return 0;
}