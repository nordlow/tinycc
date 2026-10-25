#include <stdio.h>

static assert(1);
static assert(2 + 2 == 4, "math works");

struct S {
    static assert(sizeof(int) >= 2, "int size");
};

int main(void)
{
    static assert(1, "local static assert");
    printf("OK\n");
    return 0;
}
