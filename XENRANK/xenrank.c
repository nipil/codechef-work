#include <stdio.h>

int main(int argc, char **argv)
{
    unsigned long long T, U, V, D, R, A;
    scanf("%llu", &T);
    while (T--) {
        scanf("%llu %llu", &U, &V);
        // u+v = 0 + d
        D = U + V;
        // y(n) = n * (n+1) / 2 + 1
        // x(n) = (n+1) * (n+2) / 2
        R = 1 + ((D * (D + 1)) >> 1);
        // R(u,v) = R(0,y) + u
        A = R + U;
        printf("%llu\n", A);
    }
}
