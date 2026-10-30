int printf(const char *, ...);

enum Color {
    Red,
    Green,
    Blue = 5
};

int main(void)
{
    enum Color c = Color.Green;
    printf("Red=%d, Green=%d, Blue=%d, c=%d\n", Color.Red, Color.Green, Color.Blue, c);
    return 0;
}
