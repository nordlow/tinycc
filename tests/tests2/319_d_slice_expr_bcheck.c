#include <stdio.h>

typedef int IntSlice[..];

int main(void)
{
    int a[5] = { 0, 1, 2, 3, 4 };
    IntSlice s = a[1..4];

    /* Two slice expressions in one argument list: the temporary slice
       headers must not alias each other.  */
    printf("%ld %d\n", (long)a[3..5].length, a[3..5].ptr[1]);
    printf("%ld %d %ld %d\n", (long)s[0..2].length, s[0..2].ptr[1],
           (long)s[1..3].length, s[1..3].ptr[0]);
    return 0;
}
