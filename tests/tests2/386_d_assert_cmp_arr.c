int printf(const char *, ...);

int main(void)
{
    int xs[3] = {1, 2, 3};
    int ys[3] = {1, 2, 4};
    assert(xs == ys);
    printf("OK\n");
    return 0;
}
