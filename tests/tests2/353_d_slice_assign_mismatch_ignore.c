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
    /* a mismatch copies nothing, in either direction */
    {
        int a[3] = {0, 0, 0};
        int b[5] = {1, 2, 3, 4, 5};
        Ints sa = a, sb = b;

        sa[..] = sb[..];
        show("short dst", a, 3);
        sb[..] = sa[..];
        show("long dst", b, 5);
    }

    /* equal lengths still copy */
    {
        int a[3] = {0, 0, 0};
        int b[3] = {7, 8, 9};
        Ints sa = a, sb = b;

        sa[..] = sb[..];
        show("equal", a, 3);
    }

    return 0;
}
