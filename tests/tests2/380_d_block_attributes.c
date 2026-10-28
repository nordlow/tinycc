#include <stdio.h>

void f(void) {
    @trusted {
        printf("trusted block\n");
    }
}

int main(void) {
    int x = 0;
    @trusted f();
    @trusted x = 42;
    printf("%d OK\n", x);
    return 0;
}
