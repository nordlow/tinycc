int printf(const char *, ...);

int main(void)
{
    int[] xs = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
    int[] ys = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13 };
    assert(xs == ys);
    printf("OK\n");
    return 0;
}
