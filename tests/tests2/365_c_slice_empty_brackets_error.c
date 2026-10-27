#include <stddef.h>

#if defined test_empty_lvalue
void f(void)
{
    int a[2];
    a[] = 1;
}

#elif defined test_empty_rvalue
void f(void)
{
    int a[2];
    int *p = a[];
}
#endif
