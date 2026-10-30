#include <stdio.h>

#if defined test_inferred_pure
int unannotated_pure(int x) {
    return x * x + 3;
}
int main(void) {
    printf("%d\n", unannotated_pure(5));
    return 0;
}

#elif defined test_inferred_impure
int global_counter = 0;
int unannotated_impure(int x) {
    global_counter += x;
    return global_counter;
}
int main(void) {
    printf("%d\n", unannotated_impure(10));
    printf("%d\n", unannotated_impure(5));
    return 0;
}

#elif defined test_inferred_pure_combination
int pure_helper(int a) {
    return a + 1;
}
int compute(int x) {
    return pure_helper(x) * 2;
}
int main(void) {
    printf("%d\n", compute(20));
    return 0;
}
#endif
