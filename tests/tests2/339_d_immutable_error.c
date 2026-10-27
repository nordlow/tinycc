#include <stdio.h>

struct S {
    int a;
    immutable int b;
};

struct Inner {
    int v;
};

struct Outer {
    struct Inner inner;
    int *p;
    int c;
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

#elif defined test_transitive_member
int main(void)
{
    immutable struct Outer s = {{10}, 0, 20};
    s.inner.v = 20;
    printf("%d\n", s.inner.v);
    return 0;
}

#elif defined test_transitive_pointer_member
int main(void)
{
    int z = 1;
    immutable struct Outer s = {{10}, &z, 20};
    *s.p = 2;
    printf("%d\n", *s.p);
    return 0;
}

#elif defined test_transitive_through_pointer
int main(void)
{
    struct Outer s = {{10}, 0, 20};
    immutable struct Outer *ps = &s;
    ps->inner.v = 2;
    printf("%d\n", ps->inner.v);
    return 0;
}

#elif defined test_transitive_array_element
int main(void)
{
    immutable struct Inner a[2] = {{1}, {2}};
    a[1].v = 3;
    printf("%d\n", a[1].v);
    return 0;
}

#elif defined test_immutable_pointer_write
int main(void)
{
    int z = 1;
    int * immutable p = &z;
    *p = 2;
    printf("%d\n", z);
    return 0;
}

#elif defined test_pointer_discard
int main(void)
{
    immutable int x = 1;
    immutable int *p = &x;
    int *q = p;
    printf("%p\n", (void*)q);
    return 0;
}

#elif defined test_member_pointer_discard
int main(void)
{
    immutable struct Outer s = {{10}, 0, 20};
    struct Inner *ip = &s.inner;
    printf("%d\n", ip->v);
    return 0;
}

#elif defined test_argument_discard
static void f(int *p)
{
    *p = 1;
}

int main(void)
{
    immutable int x = 1;
    immutable int *p = &x;
    f(p);
    printf("%d\n", x);
    return 0;
}

#elif defined test_return_discard
static int z;

static int *f(void)
{
    immutable int *p = &z;
    return p;
}

int main(void)
{
    printf("%d\n", *f());
    return 0;
}
#endif
