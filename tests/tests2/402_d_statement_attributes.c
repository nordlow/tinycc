#include <stdio.h>

#if defined test_trusted_for
int main(void) {
    int sum = 0;
    @trusted for (int i = 0; i < 5; i++) {
        sum += i;
    }
    printf("%d\n", sum);
    return 0;
}

#elif defined test_trusted_foreach
int main(void) {
    int sum = 0;
    int arr[3] = {10, 20, 30};
    @trusted foreach (v; arr) {
        sum += v;
    }
    printf("%d\n", sum);
    return 0;
}

#elif defined test_pure_block
int main(void) {
    int sum = 0;
    @pure {
        sum = 42;
    }
    printf("%d\n", sum);
    return 0;
}

#elif defined test_pure_for
int main(void) {
    int sum = 0;
    @pure for (int i = 0; i < 5; i++) {
        sum += i;
    }
    printf("%d\n", sum);
    return 0;
}

#elif defined test_pure_foreach
int main(void) {
    int sum = 0;
    int arr[3] = {1, 2, 3};
    @pure foreach (v; arr) {
        sum += v;
    }
    printf("%d\n", sum);
    return 0;
}
#endif
