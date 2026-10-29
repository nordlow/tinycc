#include <stdio.h>

/* With -fscope-depth=8 the function frame is depth 1 and the function
   body is depth 2, which leaves room for exactly six more nested
   scopes.  The deepest block here holds a for-loop, whose own scope
   and body use the last two levels.  */

int main(void)
{
    int x = 1;

    {
        {
            {
                {
                    int i, sum = 0;
                    for (i = 0; i < 3; i++) {
                        sum += i + x;
                    }
                    printf("%d\n", sum);
                }
            }
        }
    }
    return 0;
}
