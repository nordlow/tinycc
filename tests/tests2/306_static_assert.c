#include <stdio.h>

static assert(1);
static assert(2 + 2 == 4, "math works");
$assert(1);
$assert(2 + 2 == 4, "$assert math works");

struct S {
    static assert(sizeof(int) >= 2, "int size");
};

struct T {
    $assert(sizeof(int) >= 2, "$assert int size");
};

int main(void)
{
    static assert(1, "local static assert");
    $assert(1, "local $assert");
    printf("OK\n");
    return 0;
}
