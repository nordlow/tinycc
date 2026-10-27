#include <stdio.h>

struct Point {
    int x;
    int y;
};

struct Node {
    struct Node *next;
    int val;
};

struct Inner {
    int a;
};

struct Outer {
    struct Inner inner;
};

int main(void) {
    struct Point p = {10, 20};
    struct Point *ptr = &p;

    printf("p.x = %d, p.y = %d\n", ptr->x, ptr->y);
    printf("ptr.x = %d, ptr.y = %d\n", ptr.x, ptr.y);

    ptr.x = 100;
    ptr.y = 200;
    printf("after ptr.x = %d, ptr.y = %d\n", ptr.x, ptr.y);

    // Compound assignment corner case
    ptr.x += 50;
    ptr.y++;
    printf("compound ptr.x = %d, ptr.y = %d\n", ptr.x, ptr.y);

    // Const-qualified pointer corner case
    const struct Point *cptr = &p;
    printf("cptr.x = %d\n", cptr.x);

    // Chained pointer access
    struct Node n2 = { NULL, 42 };
    struct Node n1 = { &n2, 10 };
    struct Node *nptr = &n1;
    printf("nptr.val = %d, nptr.next.val = %d\n", nptr.val, nptr.next.val);

    // Nested struct via pointer
    struct Outer out = { { 99 } };
    struct Outer *optr = &out;
    printf("optr.inner.a = %d\n", optr.inner.a);

    return 0;
}
