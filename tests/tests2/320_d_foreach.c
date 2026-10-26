#include <stdio.h>

typedef int IntSlice[..];

int garr[4] = { 40, 41, 42, 43 };
int gs_calls;

IntSlice gs(void)
{
    gs_calls++;
    return garr[..];
}

struct P { int x, y; };

int sum(IntSlice s)
{
    int r = 0;
    foreach (v; s)
        r += v;
    return r;
}

int main(void)
{
    int a[5] = { 0, 1, 2, 3, 4 };
    IntSlice s = a[1..4];
    int n = 3;
    int vla[n];
    int i;

    /* value only, arrays and slices */
    foreach (v; a)
        printf("%d ", v);
    printf("\n");

    foreach (v; s)
        printf("%d ", v);
    printf("\n");

    /* index and value */
    foreach (i, v; a)
        printf("%d:%d ", i, v);
    printf("\n");

    foreach (i, v; s)
        printf("%d:%d ", i, v);
    printf("\n");

    /* reverse iteration */
    foreach_reverse (v; a)
        printf("%d ", v);
    printf("\n");

    foreach_reverse (i, v; s)
        printf("%d:%d ", i, v);
    printf("\n");

    /* explicit loop variable types */
    foreach (long lv; a)
        printf("%ld ", lv);
    printf("\n");

    foreach (int iv, long lv; s)
        printf("%d/%ld ", iv, lv);
    printf("\n");

    /* VLA aggregate */
    for (i = 0; i < n; i++)
        vla[i] = i + 10;
    foreach (v; vla)
        printf("%d ", v);
    printf("\n");

    /* global array and string literal */
    foreach (v; garr)
        printf("%d ", v);
    printf("\n");

    foreach (c; "abc"[0..3])
        printf("%c", c);
    printf("\n");

    /* nested loops */
    foreach (i, x; a[0..3]) {
        foreach (j, y; a[2..5])
            printf("%d ", i + j + x + y);
    }
    printf("\n");

    /* break and continue */
    foreach (i, v; a) {
        if (v == 1)
            continue;
        if (v == 3)
            break;
        printf("%d ", v);
    }
    printf("\n");

    /* the loop variable is a copy */
    foreach (v; a)
        v = -1;
    printf("%d\n", a[0]);

    /* slices as function arguments */
    printf("%d %d\n", sum(a[..]), sum(s));

    /* the aggregate expression is evaluated exactly once */
    {
        int total = 0;
        foreach (v; gs())
            total += v;
        printf("%d %d\n", gs_calls, total);
    }

    /* struct elements */
    {
        struct P ps[2] = { { 1, 2 }, { 3, 4 } };
        foreach (p; ps)
            printf("%d,%d ", p.x, p.y);
        printf("\n");
    }

    /* array elements are bound as slices */
    {
        int m[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
        foreach (row; m) {
            printf("%ld:", (long)row.length);
            foreach (v; row)
                printf("%d", v);
            printf(" ");
        }
        printf("\n");
    }

    /* empty aggregate */
    foreach (v; a[0..0])
        printf("not reached");
    foreach_reverse (v; a[0..0])
        printf("not reached");
    printf("done\n");

    /* declaration scope ends with the loop */
    foreach (v; a)
        ;
    return 0;
}
