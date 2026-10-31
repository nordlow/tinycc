#include <stdio.h>

struct File {
    int fd;
};

void process(struct File *p) {
    printf("fd=%d\n", p->fd);
}

int main() {
    @nocopy struct File f1 = { 42 };
    struct File f2 @nocopy = { 43 };

    process(&f1);
    process(&f2);
    return 0;
}
