#include <stdio.h>

typedef int[..] Ints;

int main(void)
{
    Ints a = {0};
    int base[4] = {1, 2, 3, 4};
    int i;

    for (i = 0; i < 4; ++i)
        a ~= base[i];
    a.resize(6);
    for (i = 4; i < 6; ++i)
        a[i] = i;
    printf("%d %d %d\n", (int)a.length, a[4], a[5]);

    Ints b = a.dup;
    printf("%d %d\n", (int)b.length, b[5]);

    Ints c = a ~ b;
    printf("%d %d\n", (int)c.length, c[11]);

    a.resize(2);
    printf("%d %d\n", (int)a.length, a[1]);
    return 0;
}
