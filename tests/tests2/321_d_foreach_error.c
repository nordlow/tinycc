#if defined test_pointer_aggregate
void f(int *p) { foreach (v; p) ; }

#elif defined test_scalar_aggregate
void f(void) { int x = 0; foreach (v; x) ; }

#elif defined test_too_many_variables
void f(void) { int a[2]; foreach (i, v, w; a) ; }

#elif defined test_missing_semicolon
void f(void) { int a[2]; foreach (v a) ; }

#elif defined test_missing_aggregate
void f(void) { foreach (v; ) ; }
#endif
