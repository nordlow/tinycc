#include <stdio.h>

#if defined test_inferred_safe
int unannotated_safe(int *p) {
    return *p + 1;
}
int f(void) @safe {
    int x = 41;
    return unannotated_safe(&x);
}
int main(void) {
    printf("%d\n", f());
    return 0;
}

#elif defined test_inferred_system
int unannotated_system(int *p) {
    return *(p + 1);
}
int f(void) @safe {
    int a[2] = {10, 20};
    return unannotated_system(a);
}
int main(void) { return 0; }
#endif
