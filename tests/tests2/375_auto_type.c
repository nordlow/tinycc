#include <stdio.h>

int main(void) {
    auto x = 42;
    auto y = 3.14;
    int a = 10;
    auto p = &a;
    *p = 20;
    printf("x = %d, y = %.2f, a = %d\n", x, y, a);
    return 0;
}
