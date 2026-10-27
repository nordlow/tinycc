#include <stdio.h>

typedef int[..] Ints;

int main(void)
{
    int a[3] = {0, 0, 0};
    int b[5] = {1, 2, 3, 4, 5};
    Ints sa = a, sb = b;

    printf("before\n");
    fflush(stdout);
    sa[..] = sb[..];
    printf("not reached\n");
    return 0;
}
