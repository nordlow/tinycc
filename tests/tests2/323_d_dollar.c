#include <stdio.h>

typedef int IntSlice[..];

int garr[5] = { 10, 11, 12, 13, 14 };
char gstr[4] = { 'a', 'b', 'c', 0 };

int main(void)
{
    int a[5] = { 0, 1, 2, 3, 4 };
    IntSlice s = a[1..5];
    int n = 4;
    int vla[n];
    int i;

    /* '$' is the length of the subscripted array */
    printf("%d %d %d %d\n", a[$-1], a[0], a[$/2], a[$-3]);
    printf("%ld %ld\n", (long)(a[$-1] == 4), (long)(a[$-5] == 0));

    /* ... of a slice */
    printf("%d %d %ld\n", s[$-1], s[$-2], (long)s[$/2]);

    /* ... of a global array and of a string literal */
    printf("%d %d %d\n", garr[$-1], gstr[$-1], "xyz"[$-2]);

    /* '$' in slice bounds */
    printf("%ld %d %d\n", (long)s[0..$].length, s[0..$].ptr[0],
           s[0..$].ptr[3]);
    printf("%ld %d %d\n", (long)s[1..$-1].length, s[1..$-1].ptr[0],
           s[1..$-1].ptr[2]);
    printf("%ld %d\n", (long)s[$-3..$].length, s[$-3..$].ptr[0]);

    /* ... of a VLA */
    for (i = 0; i < n; i++)
        vla[i] = i * 7;
    printf("%d %d %d\n", vla[$-1], vla[$/2], vla[0]);

    /* ... of a row of a multidimensional array */
    {
        int m[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
        printf("%d %d %ld\n", m[0][$-1], m[1][$-1], (long)m[1][0..$].length);
    }

    /* nested subscripts bind '$' to their own base */
    {
        int idx[3] = { 2, 0, 1 };
        printf("%d %d %d\n", a[idx[$-1]], a[idx[0]], a[idx[$/2]]);
    }

    /* '$' may be used in arithmetic */
    printf("%d %d\n", a[$ - 3], a[2 * $ - 9]);

    /* a variable named '$' still shadows the length inside a subscript */
    {
        int $ = 42;
        printf("%d %d\n", $, a[$ - 39]);
    }
    return 0;
}
