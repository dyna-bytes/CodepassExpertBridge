#include <iostream>
#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define FASTIO() ios_base::sync_with_stdio(false), cin.tie(NULL);
#define debug(x) cout << #x << " is " << x << endl;
typedef pair<int, int> pii;

int N, L, M;

int solve(vector<int>& ylist, vector<int>& xlist, vector<pii>& fishes) {
    sort(ylist.begin(), ylist.end());
    sort(xlist.begin(), xlist.end());
    sort(fishes.begin(), fishes.end());

    int ret = 0;
    for (int sy: ylist) {
        for (int sx: xlist) {
            for (int l = 1; l < L; l++) {
                int ey = sy + l;
                int ex = sx + L - l;

                int grab = 0;

                for (auto& [y, x]: fishes) {
                    if (sy <= y && y <= ey &&
                    sx <= x && x <= ex)
                        grab++;
                }

                // debug(sy);
                // debug(sx);
                // debug(ey);
                // debug(ex);
                // debug(grab);

                ret = max(ret, grab);
            }
        }
    }
    return ret;
}

int main() {
    FASTIO();
    cin >> N >> L >> M;
    L /= 2;

    vector<int> ylist(M), xlist(M);
    vector<pii> fishes(M);
    for (int i = 0; i < M; i++) {
        int y, x;
        cin >> y >> x;
        ylist[i] = y;
        xlist[i] = x;
        fishes[i] = {y, x};
    }

    cout << solve(ylist, xlist, fishes) << endl;

    return 0;
}