#include <stdio.h>
#include <assert.h>

static int counter;
static int twice(int x) { return 2 * x; }

unittest {
    assert(twice(3) == 6);
    counter += twice(2);
    printf("first %d\n", counter);
}

unittest {
    counter += 1;
    printf("second %d\n", counter);
}

int main(void)
{
    printf("main %d\n", counter);
    return 0;
}
