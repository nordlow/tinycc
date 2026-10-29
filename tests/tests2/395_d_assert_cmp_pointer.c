int printf(const char *, ...);

int main(void)
{
    int *a = (int *)16;
    int *b = (int *)0;
    assert(a == b);
    printf("OK\n");
    return 0;
}
