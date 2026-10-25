#include <stdio.h>

struct A { int x; int y; };
struct B { int u; int v; };
struct P { int *p; int n; };
struct Q { int *q; double d; };

typedef int IntSlice[..];
typedef int OtherIntSlice[..];
typedef long LongSlice[..];

int main(void)
{
    struct A a = { 1, 2 };
    struct A b = a;
    int arr[3] = { 10, 20, 30 };
    IntSlice s = { arr, 3 };
    OtherIntSlice t;
    t = s;

    printf("%d\n", __builtin_types_compatible_p(struct A, struct B));
    printf("%d\n", __builtin_types_compatible_p(struct P, struct Q));
    printf("%d\n", __builtin_types_compatible_p(struct A, struct A));
    printf("%d\n", __builtin_types_compatible_p(IntSlice, OtherIntSlice));
    printf("%d\n", __builtin_types_compatible_p(IntSlice, LongSlice));
    printf("%d %d\n", b.x, b.y);
    printf("%ld %d\n", (long)t.length, t.ptr[1]);
    return 0;
}
