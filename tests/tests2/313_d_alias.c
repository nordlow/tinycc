#include <stdio.h>

alias Int = int;
alias IntPtr = int *;
alias IntArr = int[3];
alias IntSlice = int[..];
alias Fn = int (*)(int);
alias FnType = int(int);

struct S { int x; };
alias SAlias = struct S;

typedef int TInt;
alias TInt = int; /* compatible redefinition across typedef/alias */

int add1(int x) { return x + 1; }
FnType *fp = add1;

int main(void)
{
    Int i = 41;
    IntPtr p = &i;
    IntArr a = { 1, 2, 3 };
    SAlias s = { 7 };
    TInt t = 5;
    alias Local = long;
    Local l = 9;
    int arr[2] = { 10, 20 };
    IntSlice sl = { arr, 2 };
    Fn f = add1;

    printf("%d %d %d %d %ld\n", i, *p, a[2], s.x, (long)l);
    printf("%ld %d %d %d\n", (long)sl.length, sl.ptr[1], f(t), fp(t));
    printf("%d %d\n",
        __builtin_types_compatible_p(Int, TInt),
        __builtin_types_compatible_p(IntSlice, int[..]));
    return 0;
}
