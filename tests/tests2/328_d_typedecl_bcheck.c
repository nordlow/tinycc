#include <stdio.h>

typedef int[..] IntSlice;
typedef int[4] Four;

int[4] g = { 1, 2, 3, 4 };

int sum(IntSlice s)
{
    int i, r = 0;
    for (i = 0; i < (int)s.length; i++)
        r += s.ptr[i];
    return r;
}

int main(void)
{
    Four a = { 10, 20, 30, 40 };
    int n = 3;
    int[n] v;
    IntSlice s = a[1..3];
    int i;

    for (i = 0; i < n; i++)
        v[i] = i + 1;

    printf("%d %d %d\n", a[0], a[3], a[1]);
    printf("%d %d %ld\n", v[0], v[2], (long)s.length);
    printf("%d %d %d\n", s.ptr[0], s.ptr[1], s.ptr[(int)s.length - 1]);
    printf("%d %d\n", sum(s), sum(g[..]));
    return 0;
}
