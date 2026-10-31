struct File {
    int fd;
};

int main() {
    @nocopy struct File f1 = { 42 };
    struct File f2 @nocopy = { 43 };
    f1 = f2;
    return 0;
}
