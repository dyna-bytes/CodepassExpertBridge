#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false), cin.tie(0);
#define endl '\n'

const int MAXN = 1001;
int N;
int arr[MAXN];

void mergeSort(int s, int e) {
    if (s >= e) return;

    int m = (s + e)/2;
    mergeSort(s, m);
    mergeSort(m + 1, e);

    int buf[MAXN];
    int l = s, r = m + 1, k = 0;
    while (l <= m && r <= e)
        if (arr[l] < arr[r]) buf[k++] = arr[l++];
        else buf[k++] = arr[r++];

    while (l <= m) buf[k++] = arr[l++];
    while (r <= e) buf[k++] = arr[r++];

    for (int i = 0; i < k; i++)
        arr[s + i] = buf[i];

    for (int i = 0; i < N; i++)
        printf("%d ", arr[i]);

    printf("\n");
}

int main() {
    scanf("%d", &N);
    for (int i = 0; i < N; i++)
        scanf("%d", &arr[i]);

    mergeSort(0, N-1);

    return 0;
}