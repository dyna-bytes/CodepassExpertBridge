#include <iostream>
#include <vector>
using namespace std;

#define MAXN 101

vector<int> A;
int N;

void insert_sort() {
    int tg;
    for (int i = 1; i <= N-1; i++) {
        tg = A[i];
        int j;
        for (j = i-1; j >= 0; j--){
            if (A[j] > tg) A[j+1] = A[j];
            else break;
        }
        A[j+1] = tg;
        for (int i = 0; i < N; i++)
            printf("%d ", A[i]);
        printf("\n");
    }
}

int main() {
    cin >> N;
    A.resize(N);

    for (int i = 0; i < N; i++) {
        cin >> A[i];
    }
    insert_sort();

    return 0;
}