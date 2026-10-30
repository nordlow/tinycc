#include <stdio.h>

struct Foo {
    int a;
    char b;
    double c;
};

int main(void) {
    int x;
    char ch;
    int arr[10];
    struct Foo f;

    // Type .sizeof
    printf("int.sizeof = %zu\n", int.sizeof);
    printf("char.sizeof = %zu\n", char.sizeof);
    printf("double.sizeof = %zu\n", double.sizeof);
    printf("struct Foo.sizeof = %zu\n", struct Foo.sizeof);
    printf("int[10].sizeof = %zu\n", int[10].sizeof);
    printf("int*.sizeof = %zu\n", int*.sizeof);

    // Parenthesized qualified types .sizeof
    printf("(int).sizeof = %zu\n", (int).sizeof);
    printf("(immutable int).sizeof = %zu\n", (immutable int).sizeof);
    printf("(const int).sizeof = %zu\n", (const int).sizeof);

    // Instance .sizeof
    printf("x.sizeof = %zu\n", x.sizeof);
    printf("ch.sizeof = %zu\n", ch.sizeof);
    printf("arr.sizeof = %zu\n", arr.sizeof);
    printf("f.sizeof = %zu\n", f.sizeof);
    printf("arr[0].sizeof = %zu\n", arr[0].sizeof);

    return 0;
}
