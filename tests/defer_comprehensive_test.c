#include <stdio.h>
#include <stdlib.h>

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
