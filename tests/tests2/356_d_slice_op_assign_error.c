#include <stddef.h>

typedef int[..] Ints;

struct S {
    int a;
};

#if defined test_slice_rhs
void f(void)
{
    int a[2];
    Ints s = a, t = a;
    s[..] += t[..];
}

#elif defined test_struct_rhs
void f(void)
{
    struct S a[2];
    struct S[..] s = a;
    struct S x = {1};
    s[..] += x;
}

#elif defined test_append
void f(void)
{
    int a[2];
    Ints s = a;
    s[..] ~= 1;
}

#elif defined test_const_op_assign
void f(void)
{
    const int b[2] = {1, 2};
    const int[..] r = b;
    r[..] += 1;
}
#endif
