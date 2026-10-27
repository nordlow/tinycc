#include <stdio.h>

$assert(1);
$assert(2 + 2 == 4, "$assert at file scope");
static assert(1, "static assert still works");

struct S {
    $assert(sizeof(int) >= 2, "$assert in struct");
};

int main(void)
{
    $assert(1, "$assert in function");
    printf("OK\n");
    return 0;
}
