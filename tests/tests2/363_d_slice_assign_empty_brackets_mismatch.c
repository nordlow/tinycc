#include <stdio.h>

typedef int[..] Ints;

int main(void)
{
    int a[3] = {1, 2, 3};
    int b[5] = {7, 8, 9, 10, 11};
    Ints x = a;
    Ints y = b;

    printf("before\n");
    fflush(stdout);
    y[] = x[];
    printf("not reached\n");
    return 0;
}
