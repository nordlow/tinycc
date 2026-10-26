#include <stdio.h>

typedef char[..] Str;

Str gs = "global";

int main(void)
{
    Str s = "hi";
    Str t = "there" " you";
    Str e = "";
    int i, n = 0;

    printf("%d %d %d %d\n", (int)s.length, (int)t.length,
           (int)e.length, (int)gs.length);
    printf("%c%c %s %s\n", s.ptr[0], s.ptr[1], t.ptr, gs.ptr);
    printf("%ld %c\n", (long)("abc"[..].length), "abc"[..].ptr[2]);

    for (i = 0; i < (int)s.length; i++)
        n += s.ptr[i];
    printf("%d\n", n);

    foreach (ch; "hey")
        putchar(ch);
    putchar('\n');

    /* the slice bounds itself are not known, so no false positives here */
    {
        Str u = s[..];
        printf("%d %c\n", (int)u.length, u.ptr[(int)u.length - 1]);
    }
    return 0;
}
