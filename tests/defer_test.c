#include <stdio.h>

void test_defer_expr() {
    int x = 42;
    defer printf("defer expr: %d\n", x);
    printf("expr main\n");
}

void test_defer_block() {
    int y = 100;
    defer {
        printf("defer block start\n");
        printf("defer block y: %d\n", y);
        printf("defer block end\n");
    }
    printf("block main\n");
}

int main() {
    test_defer_expr();
    test_defer_block();
    return 0;
}
