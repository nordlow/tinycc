#include <stdio.h>

enum x = sizeof(int) == 4;
$assert(x);

int main(void)
{
    printf("x = %d\n", x);
    return 0;
}
