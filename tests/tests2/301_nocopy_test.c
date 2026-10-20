#include <stdio.h>

struct UniqueRes {
    int fd;
} __attribute__((nocopy));

int main() {
    struct UniqueRes r1 = { 42 };
    struct UniqueRes r2;
    r2 = r1; // Assignment should fail compilation!
    return 0;
}
