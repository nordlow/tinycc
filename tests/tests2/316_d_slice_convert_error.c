typedef int IntSlice[..];

int main(void)
{
    long a[2] = { 1, 2 };
    IntSlice s = a;
    return (int)s.length;
}
