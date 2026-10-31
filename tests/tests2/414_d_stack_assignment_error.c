int *global_ptr;

void f(void) @safe {
    int x = 42;
    global_ptr = &x;
}

int main(void) {
    return 0;
}
