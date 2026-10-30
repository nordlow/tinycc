int foo(int unused_param, int _ignored_param, int used_param)
{
    int used_var = 2;
    int res = used_param + used_var;

    int unused_var = 1;

    int __attribute__((unused)) unused_attr_var = 3;

    typedef int UnusedAlias;
    typedef int UsedAlias;
    typedef int __attribute__((unused)) UnusedAttrAlias;
    
    UsedAlias ua = 4;
    res += ua;

    return res;
}

int main(void)
{
    return foo(10, 20, 40);
}
