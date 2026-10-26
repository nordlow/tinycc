#include <stdio.h>

typedef immutable int CInt;

struct S {
    int a;
    immutable int b;
};

immutable int g = 42;
immutable int ga[3] = {1, 2, 3};

int main(void)
{
    immutable int x = 7;
    CInt y = 9;
    immutable struct S s = {1, 2};
    const int *p = &x;
    int z = 5;
    int * immutable pz = &z;

    printf("%d %d %d %d\n", x, y, g, *p);
    printf("%d %d %d %d\n", s.a, s.b, ga[1], *pz);
    return 0;
}
