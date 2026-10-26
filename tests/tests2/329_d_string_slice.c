#include <stdio.h>
#include <stddef.h>

typedef char[..] Str;
typedef wchar_t[..] WStr;

Str gs = "hello";
Str gcat = "ab" "cd";
Str gempty = "";
Str garr[] = { "a", "bb", "ccc" };

struct S { int n; Str s; };
struct S gst = { 1, "abc" };

Str identity(Str s) { return s; }

static Str stat = "static";

int main(void)
{
    Str s = "hi";
    Str t = "there" " you";
    Str e = "";
    Str asg;
    char[] c = "hi";
    WStr w = L"wide";
    struct S st = { 2, "def" };
    Str larr[] = { "x", "yy" };
    int i, sum = 0;

    asg = "xy";

    /* the length of a slice excludes the terminating null character */
    printf("%d %d %d %d\n", (int)s.length, (int)t.length,
           (int)e.length, (int)gs.length);
    printf("%d %d %d %d\n", (int)gcat.length, (int)gempty.length,
           (int)asg.length, (int)stat.length);
    printf("%s|%s|%s|%s\n", s.ptr, t.ptr, e.ptr, gs.ptr);

    /* a plain C array still stores the terminating null character */
    printf("%d %d %d %d\n", (int)sizeof c, c[2], (int)sizeof("hi"),
           (int)sizeof(Str));

    /* wide string literals work the same way */
    printf("%d %d %d\n", (int)w.length, (int)w.ptr[0], (int)w.ptr[3]);

    /* slicing a string literal */
    printf("%ld %c %c\n", (long)("abc"[..].length),
           "abc"[..].ptr[0], "abc"[..].ptr[2]);
    printf("%ld\n", (long)identity("four"[..]).length);

    /* '$' is the length of the literal, without the null character */
    printf("%d %c %c\n", (int)"abc"[$ - 1], "abc"[$ - 1], "abc"[$ - 2]);

    /* foreach over a string literal */
    foreach (ch; "hey")
        putchar(ch);
    putchar('\n');
    foreach (idx, ch; "hey")
        printf("%d:%c ", idx, ch);
    putchar('\n');
    foreach_reverse (ch; "hey")
        putchar(ch);
    putchar('\n');

    /* string literals as members and as elements of an array */
    printf("%d %d %s\n", st.n, (int)st.s.length, st.s.ptr);
    printf("%d %d %s\n", gst.n, (int)gst.s.length, gst.s.ptr);
    printf("%d\n", (int)(sizeof garr / sizeof garr[0]));
    for (i = 0; i < 3; i++)
        printf("%d:%s ", (int)garr[i].length, garr[i].ptr);
    printf("\n");
    printf("%d\n", (int)(sizeof larr / sizeof larr[0]));
    for (i = 0; i < 2; i++)
        printf("%d:%s ", (int)larr[i].length, larr[i].ptr);
    printf("\n");

    /* iterating over a slice created from a literal */
    foreach (ch; gs)
        sum += ch;
    printf("%d\n", sum);

    /* a type taken from a literal is a plain array again */
    {
        typeof("hi") x;
        Str u = x[..];
        printf("%d %d %d\n", (int)u.length, (int)sizeof x, (int)sizeof("hi"));
    }
    return 0;
}
