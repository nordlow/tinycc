#include <stdio.h>

static void uncovered(void)
{
    puts("not executed");
}

int main(void)
{
    puts("ok");
    return 0;
}
