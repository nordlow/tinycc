#include <stdio.h>

int main() {
    int arr[5] = {10, 20, 30, 40, 50};
    int s[..];
    s.ptr = arr;
    s.length = 5;
    
    printf("ptr[0] = %d\n", s.ptr[0]);
    printf("length = %ld\n", (long)s.length);
    printf("ptr[2] = %d\n", s.ptr[2]);
    return 0;
}
