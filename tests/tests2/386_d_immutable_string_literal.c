#include <stdio.h>

unittest {
    immutable char *x = "a";
    $assert(__builtin_types_compatible_p(__typeof__(x), immutable char *));
}

int main(void) {
    immutable char *s = "hello";
    $assert(__builtin_types_compatible_p(__typeof__(s), immutable char *));
    printf("OK\n");
    return 0;
}
