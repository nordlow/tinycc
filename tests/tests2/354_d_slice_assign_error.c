#include <stddef.h>

typedef int[..] Ints;

#if defined test_type_mismatch
void f(void)
{
    int a[2];
    Ints s = a;
    char[..] c = "ab";
    s[..] = c;
}

#elif defined test_array_mismatch
void f(void)
{
    int a[2];
    Ints s = a;
    char c[2] = "ab";
    s[..] = c;
}

#elif defined test_append
void f(void)
{
    int a[2];
    Ints s = a;
    s[..] ~= 1;
}

#elif defined test_op_assign
void f(void)
{
    int a[2];
    Ints s = a;
    s[..] += 1;
}

#elif defined test_op_assign_sub
void f(void)
{
    int a[2];
    Ints s = a;
    s[..] -= 1;
}

#elif defined test_const_fill
void f(void)
{
    const int b[2] = {1, 2};
    const int[..] r = b;
    r[..] = 1;
}

#elif defined test_const_copy
void f(void)
{
    const int b[2] = {1, 2};
    const int[..] r = b;
    int a[2];
    Ints s = a;
    r[..] = s[..];
}
#endif
