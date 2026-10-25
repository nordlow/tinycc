#include <stdio.h>

int add(int a, int b) {
    return a + b;
}

int mul(int a, int b, int c) {
    return a * b * c;
}

int main() {
    int x = 5;
    printf("add: %d\n", x.add(10));
    printf("mul: %d\n", x.mul(2, 3));
    return 0;
}
