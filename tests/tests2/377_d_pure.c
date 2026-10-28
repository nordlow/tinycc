#include <stdio.h>

int f(int x) @pure {
    return x * 2;
}

int g(int x) @pure;

int g(int x) {
    return x + 1;
}

int main(void) {
    printf("%d %d\n", f(21), g(10));
    return 0;
}
