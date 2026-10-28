#include <stdio.h>

typedef int[..] Ints;

int main(void)
{
    int a[3] = {1, 2, 3};
    int b[3] = {1, 2, 3};
    int c[3] = {1, 2, 4};

    Ints sa = a;
    Ints sb = b;
    Ints sc = c;

    printf("slice eq: %d\n", sa == sb);
    printf("slice ne: %d\n", sa != sb);
    printf("slice ne diff: %d\n", sa != sc);

    printf("arr slice eq: %d\n", a[..] == sb);
    printf("slice arr eq: %d\n", sa == b[..]);

    int z1[0];
    int z2[0];
    Ints sz1 = z1;
    Ints sz2 = z2;
    printf("zero len eq: %d\n", sz1 == sz2);

    return 0;
}
