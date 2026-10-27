#include <stdio.h>

typedef int[..] Ints;

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
    /* every integer compound assignment is applied element-wise */
    {
        int a[6] = {1, 2, 3, 4, 5, 6};
        Ints sa = a;

        sa[..] += 2;
        show("+=", a, 6);
        sa[..] -= 1;
        show("-=", a, 6);
        sa[..] *= 3;
        show("*=", a, 6);
        sa[..] /= 2;
        show("/=", a, 6);
        sa[..] %= 7;
        show("%=", a, 6);
        a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4; a[4] = 5; a[5] = 6;
        sa[..] &= 3;
        show("&=", a, 6);
        sa[..] |= 8;
        show("|=", a, 6);
        sa[..] ^= 1;
        show("^=", a, 6);
        a[0] = 1; a[1] = 2; a[2] = 3; a[3] = 4; a[4] = 5; a[5] = 6;
        sa[..] <<= 1;
        show("<<=", a, 6);
        sa[..] >>= 2;
        show(">>=", a, 6);
    }

    /* ranges only update their own elements */
    {
        int a[5] = {1, 2, 3, 4, 5};
        Ints sa = a;
        sa[1..4] += 10;
        show("range", a, 5);
    }

    /* the right operand is evaluated once, even for an empty range */
    {
        int a[3] = {10, 20, 30};
        Ints sa = a;
        int n = 0;

        sa[..] += ++n;
        show("once", a, 3);
        printf("n=%d\n", n);

        n = 0;
        sa[1..1] += ++n;
        show("empty", a, 3);
        printf("n=%d\n", n);
    }

    /* floating point slices work too */
    {
        double d[3] = {1.5, 2.5, 3.5};
        double[..] sd = d;
        sd[..] += 0.25;
        sd[1..2] *= 2.0;
        printf("float: %g %g %g\n", d[0], d[1], d[2]);
    }

    /* char elements are widened while computing, then truncated */
    {
        signed char c[3] = {100, 101, 102};
        signed char[..] sc = c;
        sc[..] += 100;
        printf("char: %d %d %d\n", c[0], c[1], c[2]);
    }

    /* the assignment expression yields the destination slice */
    {
        int a[3] = {1, 2, 3};
        Ints sa = a;
        Ints q;

        q = (sa[..] *= 2);
        show("result", a, 3);
        printf("len=%d ptr=%d\n", (int)q.length, q.ptr == a);
    }

    return 0;
}
