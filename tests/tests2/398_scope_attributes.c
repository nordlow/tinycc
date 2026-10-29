#include <stdio.h>

#if defined test_safe_block_arith
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        p = p + 1;
    }
    return 0;
}

#elif defined test_safe_block_inc
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        ++p;
    }
    return 0;
}

#elif defined test_safe_block_index
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        return p[0];
    }
    return 0;
}

#elif defined test_safe_block_nested
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        if (1) {
            p++;
        }
    }
    return 0;
}

#elif defined test_safe_block_for
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    int i;
    @safe {
        for (i = 0; i < 1; i++) {
            p++;
        }
    }
    return 0;
}

#elif defined test_safe_block_foreach
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        foreach (v; a) {
            p++;
        }
    }
    return 0;
}

#elif defined test_safe_if_body
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    if (1) @safe {
        p++;
    }
    return 0;
}

#elif defined test_safe_system_override
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        @system {
            p++;
        }
    }
    printf("%d\n", *p);
    return 0;
}

#elif defined test_safe_trusted_override
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        @trusted {
            p++;
        }
    }
    printf("%d\n", *p);
    return 0;
}

#elif defined test_safe_no_leak
int main(void) {
    int a[2] = {10, 20};
    int *p = a;
    @safe {
        int x = 1;
        printf("%d\n", x);
    }
    p++;
    printf("%d\n", *p);
    return 0;
}

#elif defined test_function_safe_override
int f(int *p) @safe {
    @system {
        p++;
    }
    return *p;
}

int main(void) {
    int a[2] = {30, 40};
    printf("%d\n", f(a));
    return 0;
}
#endif
