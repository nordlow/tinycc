#include <stdio.h>

#if defined test_safe_add
int f(int *p) @safe {
    return *(p + 1);
}
int main(void) { return 0; }

#elif defined test_safe_sub
int f(int *p) @safe {
    return *(p - 1);
}
int main(void) { return 0; }

#elif defined test_safe_diff
int f(int *p1, int *p2) @safe {
    return p1 - p2;
}
int main(void) { return 0; }

#elif defined test_safe_inc
int f(int *p) @safe {
    ++p;
    return *p;
}
int main(void) { return 0; }

#elif defined test_safe_index
int f(int *p) @safe {
    return p[0];
}
int main(void) { return 0; }

#elif defined test_trusted_add
int f(int *p) @trusted {
    return *(p + 1);
}
int main(void) {
    int a[2] = {10, 20};
    printf("%d\n", f(a));
    return 0;
}

#elif defined test_system_add
int f(int *p) @system {
    return *(p + 1);
}
int main(void) {
    int a[2] = {30, 40};
    printf("%d\n", f(a));
    return 0;
}

#elif defined test_safe_call_system
int g(int x) @system { return x; }
int f(void) @safe {
    return g(1);
}
int main(void) { return 0; }

#elif defined test_safe_asm
int f(void) @safe {
    __asm__("");
    return 0;
}
int main(void) { return 0; }
#endif
