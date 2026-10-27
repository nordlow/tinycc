extern int puts(const char *);

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    puts(argv[1]);
    puts(argv[2]);
    return 0;
}
