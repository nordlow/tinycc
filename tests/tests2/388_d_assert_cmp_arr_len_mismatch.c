int printf(const char *, ...);

int main(void)
{
    int xs[2] = {1, 2};
    int ys[3] = {1, 2, 3};
    assert(xs == ys);
    printf("OK\n");
    return 0;
}
