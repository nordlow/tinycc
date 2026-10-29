int printf(const char *, ...);

int main(void)
{
    long double a = 1.0L / 3.0L;
    long double b = 0.5L;
    assert(a == b);
    printf("OK\n");
    return 0;
}
