#include <stdio.h>

typedef int[..] Ints;

struct P {
    int x, y;
};

struct Wrap {
    int v[3];
};

static void show(const char *tag, int *a, int n)
{
    int i;
    printf("%s:", tag);
    for (i = 0; i < n; ++i)
        printf(" %d", a[i]);
    printf("\n");
}

static int sum(Ints s)
{
    int i, n = 0;
    for (i = 0; i < (int)s.length; ++i)
        n += s.ptr[i];
    return n;
}

int main(void)
{
    int a[4] = {1, 2, 3, 4};
    int b[4] = {10, 20, 30, 40};
    Ints sa = a, sb = b, sb2 = b;

    /* y = x copies the slice header without touching the elements */
    sb = sa;
    show("header elem", b, 4);
    printf("header: len=%d ptr_a=%d\n", (int)sb.length, sb.ptr == a);

    /* y[] = x[] copies the elements of equal-length slices */
    sb2[] = sa[];
    show("copy", b, 4);
    printf("copy: len=%d ptr_b=%d\n", (int)sb2.length, sb2.ptr == b);

    /* y[] = x also accepts a slice value */
    sb2[] = sa;
    show("slice rhs", b, 4);

    /* ... including an equal-length slice range */
    sb2[] = sa[0..4];
    show("range rhs", b, 4);

    /* the assignment expression yields the destination slice */
    {
        Ints q = (sb2[] = sa[]);
        printf("result: len=%d ptr_b=%d\n", (int)q.length, q.ptr == b);
    }

    /* y[] = x fills every element with a scalar */
    sb2[] = 9;
    show("fill", b, 4);

    /* assigning an array updates the header to point at that array */
    {
        int c[2] = {5, 6};
        Ints t = a;
        t = c;
        printf("array header: len=%d ptr_c=%d\n", (int)t.length, t.ptr == c);
    }

    /* arrays work on either side */
    {
        int c[4] = {0};
        c[] = a[];
        show("array copy", c, 4);
        c[] = b;
        show("array from slice", c, 4);
        c[] = 7;
        show("array fill", c, 4);
    }

    /* empty brackets are a full slice in expression context too */
    printf("sum: %d %d\n", sum(a[]), sum(sa[]));

    /* string literals and character arrays */
    {
        char text[5] = {0};
        char word[5] = {'w', 'o', 'r', 'l', 'd'};
        text[] = "hello";
        printf("string: %.*s\n", 5, text);
        text[] = word[];
        printf("string copy: %.*s\n", 5, text);
    }

    /* aggregate elements are filled as whole values */
    {
        struct P ps[3] = {{1, 2}, {3, 4}, {5, 6}};
        struct P[..] sp = ps;
        struct P one = {8, 9};
        sp[] = one;
        printf("struct fill: %d %d %d %d\n", ps[0].x, ps[0].y,
               ps[1].x, ps[1].y);
    }

    /* empty brackets on a member of a struct */
    {
        struct Wrap w = {{1, 2, 3}};
        w.v[] = 4;
        printf("member fill: %d %d %d\n", w.v[0], w.v[1], w.v[2]);
    }

    /* zero-length slices are valid destinations */
    {
        int z[2] = {1, 2};
        Ints sz = z;
        Ints empty = z;
        empty = sz[0..0];
        empty[] = sz[0..0];
        printf("zero: %d %d len=%d\n", z[0], z[1], (int)empty.length);
    }

    /* ranges are unaffected by the empty-bracket alias */
    {
        int d[5] = {1, 2, 3, 4, 5};
        Ints sd = d;
        sd[1..4] = 8;
        show("range fill", d, 5);
        sd[0..3] = sd[1..4];
        show("range copy", d, 5);
    }

    return 0;
}
