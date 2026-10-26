#include <stdio.h>

void uncovered_func(void) {
    printf("this line is not executed\n");
}

int main(void) {
    printf("hello\n");
    fflush(stdout);
    return 0;
}
