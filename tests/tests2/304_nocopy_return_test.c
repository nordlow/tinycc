struct UniqueRes {
    int fd;
} __attribute__((nocopy));

struct UniqueRes foo() {
    struct UniqueRes r1 = { 42 };
    return r1;
}

int main() {
    return 0;
}
