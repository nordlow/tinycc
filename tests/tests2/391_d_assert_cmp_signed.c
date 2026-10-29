int printf(const char *, ...);

int main(void)
{
    short a = -300;
    short b = 300;
    assert(a == b);
    printf("OK\n");
    return 0;
}
