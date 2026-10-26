#include <stdio.h>
#include <stdlib.h>

typedef int[..] Ints;
typedef char[..] Str;

int main(void)
{
    Ints a = {0};
    int base[3] = {1, 2, 3};
    int i;

    for (i = 1; i <= 4; ++i)
        a ~= i * 10;
    printf("%d:", (int)a.length);
    foreach (x; a)
        printf(" %d", x);
    printf("\n");

    a.resize(2);
    printf("%d %d %d\n", (int)a.length, a[0], a[1]);
    a ~= 7;
    printf("%d %d\n", (int)a.length, a[2]);

    Ints b = a.dup;
    b[0] = 99;
    printf("%d %d %d\n", (int)a.length, a[0], b[0]);

    Ints c = a ~ b;
    printf("%d:", (int)c.length);
    foreach (x; c)
        printf(" %d", x);
    printf("\n");

    Ints d = base.dup;
    d ~= 4;
    printf("%d %d %d %d\n", (int)d.length, base[2], d[2], d[3]);

    Ints e = base[..] ~ a;
    printf("%d:", (int)e.length);
    foreach (x; e)
        printf(" %d", x);
    printf("\n");

    /* growing reallocates and keeps the elements */
    for (i = 0; i < 100; ++i)
        a ~= i;
    printf("%d %d %d\n", (int)a.length, a[102], a[2]);

    a.resize(0);
    printf("%d %d\n", (int)a.length, a.ptr == NULL);

    Str s = "hello" ~ " " ~ "world";
    printf("%d ", (int)s.length);
    for (i = 0; i < (int)s.length; ++i)
        putchar(s.ptr[i]);
    putchar('\n');

    Str t = s.dup;
    t.ptr[0] = 'H';
    printf("%c%c %c%c\n", s.ptr[0], s.ptr[1], t.ptr[0], t.ptr[1]);

    Str u = "abc".dup;
    u ~= '!';
    printf("%d ", (int)u.length);
    for (i = 0; i < (int)u.length; ++i)
        putchar(u.ptr[i]);
    putchar('\n');

    u.resize(0);
    typedef const int[..] ConstInts;
    ConstInts idup_base = base[..].idup;
    printf("idup: %d %d\n", (int)idup_base.length, idup_base[0]);

    u.resize(0);
    s.resize(0);
    t.resize(0);
    free(b.ptr);
    free(c.ptr);
    free(d.ptr);
    free((void *)idup_base.ptr);
}
