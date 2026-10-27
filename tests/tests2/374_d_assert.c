#include <stdio.h>

int main(void)
{
    assert(1);
    assert(2 + 2 == 4, "math works");
    printf("OK\n");
    return 0;
}
