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

int global_counter = 0;

void test_lifo_order() {
    global_counter = 0;
    defer global_counter += 3;
    defer global_counter *= 2;
    defer global_counter += 1;
}

void test_early_return(int early) {
    defer printf("unwound on return\n");
    if (early) {
        return;
    }
    printf("no early return\n");
}

void test_nested_scopes() {
    defer printf("outer scope defer\n");
    {
        defer printf("inner scope defer 1\n");
        defer printf("inner scope defer 2\n");
    }
}

int main() {
    test_defer_expr();
    test_defer_block();

    printf("--- testing lifo order ---\n");
    test_lifo_order();
    printf("global_counter = %d (expected 5)\n", global_counter);

    printf("--- testing early return (true) ---\n");
    test_early_return(1);

    printf("--- testing early return (false) ---\n");
    test_early_return(0);

    printf("--- testing nested scopes ---\n");
    test_nested_scopes();

    return 0;
}
