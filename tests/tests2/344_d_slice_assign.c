#include <stdio.h>
#include <stdlib.h>

typedef int[..] Ints;

int main(void)
{
    int base1[3] = {1, 2, 3};
    int base2[3] = {10, 20, 30};
    Ints s1 = base1;
    Ints s2 = base2;

    s1[..] = s2[..];
    printf("copy: %d %d %d\n", s1[0], s1[1], s1[2]);

    s1[..] = 42;
    printf("fill: %d %d %d\n", s1[0], s1[1], s1[2]);

    return 0;
}
