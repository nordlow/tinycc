#include <stdio.h>

version (unittest) int selected = 1; else int selected = 0;

int main(void)
{
    version (unittest) printf("version unittest on\n"); else printf("version unittest off\n");
    debug printf("debug on\n"); else printf("debug off\n");
    printf("selected %d\n", selected);
    return 0;
}
