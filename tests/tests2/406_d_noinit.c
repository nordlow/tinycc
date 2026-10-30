#include <stdio.h>

int g1 = void;
@noinit int g2;
int g3 @noinit;

int main(void)
{
    int l1 = void;
    @noinit int l2;
    int l3 @noinit;

    g1 = 10;
    g2 = 20;
    g3 = 30;
    l1 = 40;
    l2 = 50;
    l3 = 60;

    printf("g1=%d, g2=%d, g3=%d\n", g1, g2, g3);
    printf("l1=%d, l2=%d, l3=%d\n", l1, l2, l3);
    return 0;
}
