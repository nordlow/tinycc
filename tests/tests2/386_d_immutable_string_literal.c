#include <stdio.h>

unittest {
    immutable char *x = "a";
    $assert(__builtin_types_compatible_p(__typeof__(x), immutable char *));
    $assert(sizeof("a") == 2);
    $assert(__builtin_types_compatible_p(__typeof__("a"), immutable char[2]));
}

int main(void) {
    immutable char *s = "hello";
    $assert(__builtin_types_compatible_p(__typeof__(s), immutable char *));
    $assert(sizeof("hello") == 6);
    $assert(__builtin_types_compatible_p(__typeof__("hello"), immutable char[6]));
    printf("OK\n");
    return 0;
}
