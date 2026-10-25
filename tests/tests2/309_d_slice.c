#include <stdio.h>

void print_slice(int s[...]) {
    printf("func len = %ld, ptr[0] = %d\n", (long)s.length, s.ptr[0]);
}

int main() {
    int arr[3] = {100, 200, 300};
    int s[..] = { .length = 3, .ptr = arr };

    printf("s.length = %ld\n", (long)s.length);
    printf("s.ptr[1] = %d\n", s.ptr[1]);

    print_slice(s);
    return 0;
}
