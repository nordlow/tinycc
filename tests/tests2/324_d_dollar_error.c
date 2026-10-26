#if defined test_pointer_subscript
void f(int *p) { int x = p[$-1]; }

#elif defined test_scalar_subscript
void f(void) { int x = 1; int y = x[$-1]; }

#elif defined test_outside_subscript
void f(void) { int x = $; }
#endif
