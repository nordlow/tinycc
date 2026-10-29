#include <stdio.h>

int x @static = 42;
@static int y = 100;

int main(void) {
    printf("%d %d\n", x, y);
    return 0;
}
