/* A .d source extension is compiled like a C source file, which is
   what makes the tdc wrapper usable with D-style file names. */
#include <stdio.h>

int main(void)
{
    int x = 42;
    printf("%zu %d\n", x.sizeof, x);
    return 0;
}
