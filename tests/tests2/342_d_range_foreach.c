#include <stdio.h>

int main(void)
{
    printf("forward:");
    foreach (i; 0 .. 5)
        printf(" %d", i);
    printf("\n");

    printf("reverse:");
    foreach_reverse (i; 0 .. 5)
        printf(" %d", i);
    printf("\n");

    printf("explicit type:");
    foreach (int i; 10 .. 13)
        printf(" %d", i);
    printf("\n");

    printf("break:");
    foreach (i; 0 .. 10) {
        if (i == 3)
            break;
        printf(" %d", i);
    }
    printf("\n");

    printf("continue:");
    foreach (i; 0 .. 5) {
        if (i == 2)
            continue;
        printf(" %d", i);
    }
    printf("\n");

    printf("empty range:");
    foreach (i; 5 .. 5) {
        printf(" %d", i);
    }
    printf(" done\n");

    return 0;
}
