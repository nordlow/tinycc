int printf(const char *, ...);

int main(void)
{
    char a = 'a';
    char b = '\n';
    assert(a == b);
    printf("OK\n");
    return 0;
}
