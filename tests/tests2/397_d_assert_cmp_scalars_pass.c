#include <stdbool.h>

int printf(const char *, ...);

int main(void)
{
    bool t = true;
    bool u = true;
    char c = 'a';
    char k = 'a';
    short s = -3;
    short w = -3;
    unsigned long long n = 18446744073709551615ULL;
    unsigned long long m = 18446744073709551615ULL;
    int i = -3;
    int j = -3;
    int *p = (int *)0;
    int *q = (int *)0;
    float f = 2.5f;
    float g = 2.5f;
    double d = 0.5;
    double e = 0.5;
    double nz = -0.0;
    double pz = 0.0;
    long double ld = 0.25L;
    long double le = 0.25L;

    assert(t == u);
    assert(c == k);
    assert(s == w);
    assert(n == m);
    assert(i == j);
    assert(p == q);
    assert(f == g);
    assert(d == e);
    assert(nz == pz);
    assert(ld == le);
    /* mixed scalar types are compared with the usual conversions */
    assert(i <= f);
    assert(d < f);
    assert(s == i);
    printf("OK\n");
    return 0;
}
