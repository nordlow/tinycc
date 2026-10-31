#include <stdio.h>

int main() {
    @final int x = 42;
    @final int y;
    y = 100;
    printf("x=%d, y=%d\n", x, y);
    return 0;
}
