#if defined test_incomplete_element
void f(void) { void[3] x; }

#elif defined test_negative_size
void f(void) { int[-1] x; }

#elif defined test_too_many_initializers
void f(void) { int[2] x = { 1, 2, 3 }; }

#elif defined test_function_returning_array
int[3] f(void);

#elif defined test_missing_declarator
int[3] = 1;

#elif defined test_parameter_suffix
void f(int[3] a);
#endif
