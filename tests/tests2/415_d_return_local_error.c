int *f(void) @safe {
    int x = 42;
    return &x;
}

int main(void) {
    return 0;
}
