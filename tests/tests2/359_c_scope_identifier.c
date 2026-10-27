#include <stdio.h>

static int scope(int x)
{
    return x + 1;
}

int main(void)
{
    int exit = 41;
    {
        int scope = 7;
        printf("%d\n", scope);
    }
    printf("%d\n", scope(exit));
    return 0;
}
