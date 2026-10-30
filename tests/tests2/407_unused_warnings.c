int foo(int unused_param, int _ignored_param)
{
    int unused_var = 1;
    (void)unused_var;
    typedef int UnusedAlias;
    return 0;
}

int main(void)
{
    return foo(10, 20);
}
