#include <stdio.h>
#include <string.h>

typedef int[..] Ints;

struct P {
    int x, y;
};

static void show(const char *tag, int *a, int n)
{
    int i;
    printf("%s:", tag);
    for (i = 0; i < n; ++i)
        printf(" %d", a[i]);
    printf("\n");
}

int main(void)
{
    int a[4] = {1, 2, 3, 4};
    int b[4] = {10, 20, 30, 40};
    Ints sa = a, sb = b;
    Ints q;

    /* copying a whole slice also yields the destination slice */
    q = (sa[..] = sb[..]);
    show("copy", a, 4);
    printf("result: len=%d ptr=%d\n", (int)q.length, q.ptr == a);

    /* an array right operand is converted to a slice and copied */
    {
        int c[4] = {5, 6, 7, 8};
        sa[..] = c;
        show("array", a, 4);
    }

    /* a string literal is an array of char */
    {
        char buf[5] = {0};
        char[..] cb = buf;
        cb[..] = "hello";
        printf("string: %s\n", buf);

        char small[9] = {0};
        char[..] sbuf = small;
        sbuf[2..7] = "world";
        printf("substring: '%s'\n", small + 2);
    }

    /* subrange to subrange copies */
    {
        int d[6] = {1, 2, 3, 4, 5, 6};
        Ints sd = d;
        sd[1..4] = sd[2..5];
        show("range", d, 6);
        sd[0..2] = sb[0..2];
        show("range2", d, 6);
    }

    /* filling whole and partial ranges */
    {
        int d[5] = {0};
        Ints sd = d;
        sd[..] = 7;
        show("fill", d, 5);
        sd[1..3] = 8;
        show("fill2", d, 5);
    }

    /* arrays can be destinations without an explicit slice */
    {
        int d[4] = {0};
        int e[4] = {1, 2, 3, 4};

        d[..] = e[..];
        show("arr copy", d, 4);
        d[1..3] = 9;
        show("arr fill", d, 4);
        d[0..2] = e[2..4];
        show("arr range", d, 4);

        char s[5] = {0};
        s[..] = "abcde";
        printf("arr string: %s\n", s);
    }

    /* '$' in a range denotes the length */
    {
        int d[4] = {0};
        Ints sd = d;
        sd[1..$] = 3;
        show("dollar", d, 4);
    }

    /* a pointer base can be filled through a range */
    {
        int d[4] = {0};
        int *p = d;
        p[0..2] = 9;
        show("pointer", d, 4);
    }

    /* a slice value and a conditional expression are valid right operands */
    {
        Ints t = sb;

        sa[..] = t;
        show("slice value", a, 4);
        sa[..] = (a[0] > 0 ? sb[..] : t[..]);
        show("conditional", a, 4);
    }

    /* struct elements are copied element-wise as values */
    {
        struct P ps[3] = {{1, 2}, {3, 4}, {5, 6}};
        struct P[..] sp = ps;
        struct P one = {8, 9};

        sp[0..2] = one;
        printf("struct fill: %d %d %d %d\n", ps[0].x, ps[0].y,
               ps[1].x, ps[1].y);
        sp[2..3] = sp[0..1];
        printf("struct copy: %d %d %d %d\n", ps[2].x, ps[2].y,
               ps[0].x, ps[0].y);
    }

    /* aggregate elements are filled as whole values too */
    {
        struct Q { int v[2]; } qs[2] = {{{1, 2}}, {{3, 4}}};
        struct Q one = {{7, 8}};
        struct Q[..] sq = qs;

        sq[0..2] = one;
        printf("aggregate fill: %d %d %d %d\n", qs[0].v[0], qs[0].v[1],
               qs[1].v[0], qs[1].v[1]);
    }

    /* zero-length assignments are no-ops, but valid */
    {
        int d[3] = {1, 2, 3};
        Ints sd = d;
        sd[0..0] = 4;
        sd[2..2] = sd[0..0];
        show("zero", d, 3);
    }

    /* overlapping ranges must behave like memmove */
    {
        int d[5];
        Ints sd = d;

        memcpy(d, (int[]){1, 2, 3, 4, 5}, sizeof d);
        sd[0..3] = sd[1..4];
        show("overlap fwd", d, 5);

        memcpy(d, (int[]){1, 2, 3, 4, 5}, sizeof d);
        sd[1..4] = sd[0..3];
        show("overlap bwd", d, 5);
    }

    /* copies of equal-length slices never touch the length policy */
    {
        int d[3] = {0, 0, 0};
        int e[3] = {1, 2, 3};
        Ints sd = d, se = e;
        sd[..] = se[..];
        show("equal", d, 3);
    }

    return 0;
}
