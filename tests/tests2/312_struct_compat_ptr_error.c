struct P { int *p; int n; };
struct Q { int *q; double d; };

int main(void)
{
    struct P p = { 0, 0 };
    struct Q q = { 0, 0 };
    p = q;
    return 0;
}
