typedef int[..] Ints;

#if defined test_length_array
void f(void) { int a[3]; a.length = 0; }

#elif defined test_resize_array
void f(void) { int a[3]; a.resize(0); }

#elif defined test_append_nonslice
void f(void) { int x = 1; x ~= 2; }

#elif defined test_concat_nonslice
void f(void) { Ints a = {0}; Ints b = a ~ 1; }

#elif defined test_concat_mismatch
void f(void) { Ints a = {0}; char[..] c = "x"; Ints b = a ~ c; }

#elif defined test_dup_scalar
void f(void) { int x = 1; x.dup; }
#endif
