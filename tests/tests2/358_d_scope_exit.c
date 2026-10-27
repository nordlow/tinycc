#include <stdio.h>

static int order[8];
static int norder;

static void push(int v)
{
    order[norder++] = v;
}

static void show(const char *tag)
{
    int i;
    printf("%s:", tag);
    for (i = 0; i < norder; ++i)
        printf(" %d", order[i]);
    printf("\n");
    norder = 0;
}

static void statement_guard(void)
{
    int x = 41;
    scope(exit) push(x + 1);
    push(1);
}

static void block_guard(void)
{
    int x = 7;
    scope(exit) {
        push(x);
        push(x + 1);
    }
    push(0);
}

static void lifo_guard(void)
{
    defer push(1);
    scope(exit) push(2);
    defer {
        push(3);
        push(4);
    }
    scope(exit) push(5);
    push(0);
}

static void early_return(int early)
{
    scope(exit) push(9);
    if (early)
        return;
    push(8);
}

static void nested_guard(void)
{
    scope(exit) push(1);
    {
        scope(exit) {
            push(2);
            push(3);
        }
        push(4);
    }
    push(5);
}

int main(void)
{
    statement_guard();
    show("statement");

    block_guard();
    show("block");

    lifo_guard();
    show("lifo");

    early_return(1);
    show("early return");
    early_return(0);
    show("normal return");

    nested_guard();
    show("nested");

    return 0;
}
