#include <stdio.h>

typedef int IntSlice[..];

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

    printf("%d %d\n", sum(a[..]), sum(s));
    foreach (i, v; s)
        printf("%d:%d ", i, v);
    printf("\n");
    foreach_reverse (v; a[1..4])
        printf("%d ", v);
    printf("\n");
    return 0;
}
