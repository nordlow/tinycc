#include <stdio.h>

void f(void) {
    @trusted {
        printf("trusted block\n");
    }
}

int main(void) {
    @safe {
        @system {
            @pure {
                f();
            }
        }
    }
    printf("OK\n");
    return 0;
}
