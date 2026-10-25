#include <stdio.h>

typedef int IntSlice[..];

int garr[3] = { 7, 8, 9 };
IntSlice gs = garr;

int sum(IntSlice s)
{
    int i, r = 0;
    for (i = 0; i < (int)s.length; i++)
        r += s.ptr[i];
    return r;
}

IntSlice tail(int *p, int n)
{
    static int buf[4];
    int i;
    for (i = 0; i < n; i++)
        buf[i] = p[i];
    return buf;
}

int main(void)
{
    int arr[3] = { 1, 2, 3 };
    IntSlice s = arr;
    IntSlice t;
    IntSlice u;
    IntSlice e = { .length = 2, .ptr = arr + 1 };
    int n = 2;
    int vla[n];

    printf("%ld %d %d %d\n", (long)s.length, s.ptr[0], s.ptr[1], s.ptr[2]);
    /* .length comes before .ptr (D ABI) */
    printf("%d\n", (int)((char *)&s.ptr - (char *)&s) / (int)sizeof(void *));
    printf("%d %d\n", sum(arr), sum(gs));
    t = arr;
    printf("%ld %d\n", (long)t.length, t.ptr[2]);
    u = tail(arr, 3);
    printf("%ld %d %d %d\n", (long)u.length, u.ptr[0], u.ptr[1], u.ptr[2]);
    printf("%ld %d %d\n", (long)e.length, e.ptr[0], e.ptr[1]);
    vla[0] = 4;
    vla[1] = 5;
    {
        IntSlice vs = vla;
        printf("%ld %d %d\n", (long)vs.length, vs.ptr[0], vs.ptr[1]);
    }
    return 0;
}
