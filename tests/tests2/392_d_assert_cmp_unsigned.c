int printf(const char *, ...);

int main(void)
{
    unsigned long long a = 18446744073709551615ULL;
    unsigned long long b = 1ULL;
    assert(a == b);
    printf("OK\n");
    return 0;
}
