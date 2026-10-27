#include <stdio.h>

static void fully_uncovered(void)
{
    puts("never");
    puts("also never");
}

static void partially_covered(int x)
{
    if (x)
        puts("covered branch");
    else
        puts("uncovered branch");
}

int main(void)
{
    puts("hello");
    partially_covered(1);
    fflush(stdout);
    return 0;
}
