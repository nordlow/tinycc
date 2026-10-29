#include <stdbool.h>

int printf(const char *, ...);

int main(void)
{
    bool a = true;
    bool b = false;
    assert(a == b);
    printf("OK\n");
    return 0;
}
