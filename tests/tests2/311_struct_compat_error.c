struct A { int x; int y; };
struct B { int u; int v; };

int main(void)
{
    struct A a = { 0, 0 };
    struct B b = { 0, 0 };
    a = b;
    return 0;
}
