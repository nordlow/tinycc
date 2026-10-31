#include <stdlib.h>

int *global_ptr;

int *test_return_heap_ptr(void) @safe {
    int *al = (int *)malloc(sizeof(int));
    return al;
}

int *test_return_param_ptr(int *buf) @safe {
    return buf;
}

void test_assign_heap_ptr(void) @safe {
    int *p = (int *)malloc(sizeof(int));
    global_ptr = p;
}

int main(void) {
    int *p = test_return_heap_ptr();
    test_return_param_ptr(p);
    test_assign_heap_ptr();
    free(p);
    return 0;
}
