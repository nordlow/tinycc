#include <stdio.h>

#if defined test_global_var
int global_var = 42;
int f(void) @pure {
    return global_var;
}
int main(void) { return 0; }

#elif defined test_static_var
int f(void) @pure {
    static int static_var = 0;
    return static_var++;
}
int main(void) { return 0; }

#elif defined test_tls_var
__thread int tls_var = 10;
int f(void) @pure {
    return tls_var;
}
int main(void) { return 0; }

#elif defined test_global_member
struct Point { int x, y; } g_pt = {1, 2};
int f(void) @pure {
    return g_pt.x;
}
int main(void) { return 0; }

#elif defined test_pure_local_pass
int f(int *p) @pure {
    return *p + 1;
}
int main(void) {
    int x = 10;
    printf("%d\n", f(&x));
    return 0;
}
#endif
