#include <stdio.h>

struct S {
    int a;
    immutable int b;
};

#if defined test_scalar
int main(void)
{
    immutable int x = 1;
    x = 2;
    printf("%d\n", x);
    return 0;
}

#elif defined test_member
int main(void)
{
    struct S s = {1, 2};
    s.b = 3;
    printf("%d\n", s.b);
    return 0;
}

#elif defined test_aggregate_member
int main(void)
{
    immutable struct S s = {1, 2};
    s.a = 3;
    printf("%d\n", s.a);
    return 0;
}

#elif defined test_array_element
int main(void)
{
    immutable int a[2] = {1, 2};
    a[0] = 3;
    printf("%d\n", a[0]);
    return 0;
}

#elif defined test_pointer_target
int main(void)
{
    immutable int x = 1;
    immutable int *p = &x;
    *p = 2;
    printf("%d\n", x);
    return 0;
}
#endif
