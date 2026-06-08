#include <stdio.h>
#define debug(x) printf("%s is %lld\n", #x, x);
#define min(a, b) (a) < (b) ? (a) : (b)
#define max(a, b) (a) > (b) ? (a) : (b)

struct square_t {
    int x, y, p, q;
    bool operator < (const square_t& other) {
        if (x == other.x && y == other.y && p == other.p) return q < other.q;
        if (x == other.x && y == other.y) return p < other.p;
        if (x == other.x) return y < other.y;
        return x < other.x;
    }
};

int solve(square_t& A, square_t& B) {
    if (A.x <= B.p && B.x <= A.p
    && A.y <= B.q && B.y <= A.q) {
        if (A.x == B.p || B.x == A.p
        || A.y == B.q || B.y == A.q) {
            if ((A.x == B.p || B.x == A.p) && (A.y < B.q && B.y < A.q))
                return 1;
            else if ((A.y == B.q || B.y == A.q) && (A.x < B.p && B.x < A.p))
                return 1;
            return 2;
        }
        return 0;
    } else return 3;
}

int main() {
    for (int i = 0; i < 4; i++) {
        square_t A, B;
        scanf("%d %d %d %d", &A.x, &A.y, &A.p, &A.q);
        scanf("%d %d %d %d", &B.x, &B.y, &B.p, &B.q);

        if (!(A < B)) {
            square_t t = A;
            A = B;
            B = t;
        }

        int ret = solve(A, B);
        if (ret == 0) printf("a\n");
        else if (ret == 1) printf("b\n");
        else if (ret == 2) printf("c\n");
        else if (ret == 3) printf("d\n");
    }
    return 0;
}