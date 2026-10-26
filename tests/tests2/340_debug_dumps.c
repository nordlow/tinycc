#include <stdio.h>

int global_var = 42;

int add(int a, int b) {
    return a + b;
}

int main(void) {
    int x = 10;
    int y = 20;
    int z = add(x, y);
    printf("z = %d\n", z);
    return 0;
}
