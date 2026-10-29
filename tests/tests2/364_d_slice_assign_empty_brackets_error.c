#include <stddef.h>

typedef int[..] Ints;

#if defined test_pointer
void f(void)
{
    int *p = 0;
    p[] = 1;
}

#elif defined test_scalar
void f(void)
{
    int x = 0;
    x[] = 1;
}

#elif defined test_slice_type_mismatch
void f(void)
{
    int a[2];
    Ints s = a;
    immutable char[..] c = "ab";
    s[] = c[];
}

#elif defined test_array_type_mismatch
void f(void)
{
    int a[2];
    Ints s = a;
    char c[2] = "ab";
    s[] = c;
}
#endif
