#include <stdio.h>

int[3] ga = { 1, 2, 3 };
int[] gb = { 4, 5, 6, 7 };
static int[2] gs = { 8, 9 };
const int[2] gc = { 10, 11 };
unsigned[2] gu = { 12u, 13u };

typedef int[4] Four;
typedef int[..] IntSlice;
typedef Four[2] TwoFour;
typedef int[3]* ThreePtr;

Four g4 = { 1, 2, 3, 4 };
TwoFour g24 = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 } };

struct S {
    int[2] a;
    Four b;
    IntSlice s;
};

extern int[3] ext;
int ext[3] = { 7, 8, 9 };

/* the suffix is part of the type, so it applies to every declarator */
int[2] ca, cb;
typedef int[2] TwoA, TwoB;
alias AliasTwoThree = int[2][3];

int sum(Four a)
{
    int i, r = 0;
    for (i = 0; i < 4; i++)
        r += a[i];
    return r;
}

int sumslice(IntSlice s)
{
    int i, r = 0;
    for (i = 0; i < (int)s.length; i++)
        r += s.ptr[i];
    return r;
}

int main(void)
{
    int[4] a = { 10, 20, 30, 40 };
    /* array suffixes apply left to right: an array of 3 arrays of
       2 ints, i.e. 'int m[3][2]' in C */
    int[2][3] m = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
    int[4]* p = &a;
    int n = 4;
    int[n] v;
    int i;

    for (i = 0; i < n; i++)
        v[i] = i + 1;

    printf("%d %d %d %d %d %d\n", ga[0], ga[2], gb[0], gb[3], gs[1], ext[1]);
    printf("%d %d %u %d\n", gc[0], gc[1], gu[1], g4[3]);
    printf("%d %d %d %d\n", g24[0][3], g24[1][0], g24[1][3], sum(g24[1]));
    printf("%d %d %d\n", a[0], a[3], sum(a));
    printf("%d %d %d %d\n", m[0][0], m[0][1], m[2][0], m[2][1]);
    printf("%d %d\n", (*p)[0], (*p)[3]);
    printf("%d %d %ld\n", v[0], v[3], (long)(sizeof v / sizeof v[0]));

    /* D-style arrays convert to slices implicitly */
    {
        IntSlice s = a[..];
        IntSlice t = gb[1..3];
        printf("%d %d %ld %ld\n", s.ptr[1], t.ptr[1],
               (long)s.length, (long)t.length);
        printf("%d %d\n", sumslice(s), sumslice(t));
    }

    /* struct members */
    {
        struct S st;
        st.a[0] = 5;
        st.a[1] = 6;
        st.b[3] = 7;
        st.s = ga[..];
        printf("%d %d %d %d %ld\n", st.a[0], st.a[1], st.b[3],
               st.s.ptr[2], (long)st.s.length);
    }

    /* typeof and declarations in a for statement */
    {
        typeof(a) b;
        b[0] = 9;
        b[2] = 7;
        printf("%d %d %d\n", b[0], b[2], (int)sizeof b);
    }
    for (int[2] pair = { 1, 2 }; pair[0] < 3; pair[0]++)
        printf("%d,%d ", pair[0], pair[1]);
    printf("\n");

    /* pointer to array through a typedef */
    {
        ThreePtr tp = &ga;
        printf("%d %d\n", (*tp)[1], (*tp)[2]);
    }

    /* one suffix, several declarators */
    {
        TwoA ta = { 1, 2 };
        TwoB tb = { 3, 4 };
        AliasTwoThree am = { { 1, 2 }, { 3, 4 }, { 5, 6 } };
        ca[0] = 8;
        cb[1] = 9;
        printf("%d %d %d %d %d %d\n", ca[0], cb[1],
               (int)sizeof ca, (int)sizeof cb, ta[1], tb[0]);
        printf("%d %d %d\n", (int)sizeof(AliasTwoThree),
               am[0][1], am[2][0]);
    }

    /* C declarators are unaffected and keep their own ordering */
    {
        int c[3] = { 1, 2, 3 };
        int cm[2][3] = { { 1, 2, 3 }, { 4, 5, 6 } };
        int (*cp)[2][3] = &cm;
        printf("%d %d %d %d %d\n", c[2], cm[1][2], (*cp)[1][2],
               (int)sizeof(int[3]), (int)sizeof(int[2][3]));
    }
    return 0;
}
