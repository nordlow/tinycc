struct UniqueRes {
    int fd;
} __attribute__((nocopy));

void foo(struct UniqueRes r) {
}

int main() {
    struct UniqueRes r1 = { 42 };
    foo(r1);
    return 0;
}
