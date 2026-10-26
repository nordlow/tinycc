#include <stdio.h>

enum x = 42;
enum int y = 100;
enum long z = 1000L;

int main(void)
{
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %ld\n", z);

    enum local_const = 999;
    printf("local_const = %d\n", local_const);
    return 0;
}
