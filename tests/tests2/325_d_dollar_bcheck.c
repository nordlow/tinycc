#include <stdio.h>

typedef int IntSlice[..];

int main(void)
{
    int a[5] = { 0, 1, 2, 3, 4 };
    IntSlice s = a[1..4];
    int n = 3;
    int vla[n];
    int i;

    for (i = 0; i < n; i++)
        vla[i] = i + 1;

    printf("%d %d %d\n", a[$-1], s[$-1], a[$/2]);
    printf("%ld %d %ld\n", (long)s[0..$].length, s[0..$].ptr[0],
           (long)s[1..$-1].length);
    printf("%d %d\n", s[$-2..$].ptr[0], s[$-2..$].ptr[1]);
    printf("%d %d\n", vla[$-1], vla[0]);
    return 0;
}
