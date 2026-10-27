#include <stdio.h>

static int version = 1;
static int debug = 2;

int main(void)
{
    int version_local = 3;
    version += 4;
    debug *= 5;
    printf("%d %d %d\n", version, debug, version_local);
    return 0;
}
