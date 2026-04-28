#include <stdio.h>
#include <string.h>

const int MAXN = 1e6 + 10;
char inp[MAXN];
char out[MAXN];

int solve(char* str, char* ret) {
    int n = strlen(str);

    int opens = 0;
    int sum_opens = 0;
    int rotations = 0;
    for (int i = 0; i < n; i++) {
        if (str[i] == 'C') {
            if (sum_opens < n/2) {
                ret[i] = '(';
                opens++;
                sum_opens++;
            } else {
                ret[i] = ')';
                opens--;
                rotations += 2;
            }
        } else if (str[i] == 'U') {
            if (opens > 0) {
                ret[i] = ')';
                opens--;
                rotations++;
            } else {
                ret[i] = '(';
                opens++;
                rotations++;
                sum_opens++;
            }
        }
    }

    ret[n] = '\0';
    return rotations;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", inp);

        int rotations = solve(inp, out);
        printf("%d\n", rotations);
        printf("%s\n", out);
    }
    return 0;
}