#include <stdio.h>

int f(int x) @safe {
    return x + 1;
}

int g(int x) @system {
    return x + 2;
}

int h(int x) @trusted {
    return x + 3;
}

int main(void) {
    printf("%d %d %d\n", f(1), g(2), h(3));
    return 0;
}
