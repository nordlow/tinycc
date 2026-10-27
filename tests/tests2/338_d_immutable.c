#include <stdio.h>

typedef immutable int CInt;

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

immutable int g = 42;
immutable int ga[3] = {1, 2, 3};
immutable struct Outer go = {{10}, 0, 20};
immutable struct Inner gia[2] = {{11}, {12}};

static int read_immutable(immutable int a)
{
    return a;
}

static int read_through(immutable int *p, immutable struct Inner i)
{
    return *p + i.v;
}

int main(void)
{
    immutable int x = 7;
    CInt y = 9;
    immutable struct S s = {1, 2};
    const int *p = &x;
    int z = 5;
    int * immutable pz = &z;
    immutable int *ip = &x;
    int *mp = &z;
    immutable int *mpi = mp; /* mutable -> immutable is allowed */
    const int *cpi = ip;     /* immutable -> const is allowed */
    struct Outer o = {{1}, 0, 2};
    struct Inner in = {3};
    struct Inner mia[2] = {{1}, {2}};
    struct S ms = {8, 9};
    immutable struct Outer *ps = &o;

    printf("%d %d %d %d\n", x, y, g, *p);
    printf("%d %d %d %d %d\n", s.a, s.b, ga[1], *pz, go.inner.v);
    printf("%d %d %d %d\n", *mpi, *cpi, ps->inner.v, go.c);
    printf("%d\n", gia[1].v);
    printf("%d %d\n", read_immutable(x), read_through(mp, in));

    /* The aggregate types above are used both with and without
       'immutable'.  The mutable uses must stay fully writable, even
       after immutable members have been read.  */
    o.inner.v = 4;
    o.c = 5;
    in.v = 6;
    mia[0].v = 7;
    ms.a = 8;
    printf("%d %d %d %d %d\n", o.inner.v, o.c, in.v, mia[0].v, ms.a);
    return 0;
}
