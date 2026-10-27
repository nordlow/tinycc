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
    /* destination shorter than the source: copy the common prefix */
    {
        int a[3] = {0, 0, 0};
        int b[5] = {1, 2, 3, 4, 5};
        Ints sa = a, sb = b;

        sa[..] = sb[..];
        show("short dst", a, 3);
    }

    /* destination longer than the source: the tail is left alone */
    {
        int a[5] = {9, 9, 9, 9, 9};
        int b[3] = {1, 2, 3};
        Ints sa = a, sb = b;

        sa[..] = sb[..];
        show("long dst", a, 5);
    }

    /* equal lengths are a full copy */
    {
        int a[3] = {0, 0, 0};
        int b[3] = {7, 8, 9};
        Ints sa = a, sb = b;

        sa[..] = sb[..];
        show("equal", a, 3);
    }

    return 0;
}
