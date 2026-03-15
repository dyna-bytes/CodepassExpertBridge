#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define FASTIO ios::sync_with_stdio(false), cin.tie(0);
#define endl '\n'

void solve(int N, vector<int>& arr) {
    for (int i = 1, j; i < N; i++) {
        int target = arr[i];
        for (j = i - 1; j >= 0; j--) {
            if (arr[j] > target) arr[j + 1] = arr[j];
            else break;
        }

        arr[j + 1] = target;

        for (int n: arr) cout << n << " ";
        cout << endl;
    }
}

int main() {
    FASTIO;
    int N; cin >> N;
    vector<int> arr;
    arr.resize(N);
    for (int i = 0; i < N; i++)
        cin >> arr[i];

    solve(N, arr);
    return 0;
}