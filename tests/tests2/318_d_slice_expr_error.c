#if defined test_pointer_full_slice
typedef int IntSlice[..];
void f(int *p) { IntSlice s = p[..]; }

#elif defined test_static_slice_expr
typedef int IntSlice[..];
int ga[3] = { 1, 2, 3 };
IntSlice g = ga[1..3];

#elif defined test_missing_upper_bound
typedef int IntSlice[..];
void f(void) { int a[3]; IntSlice s = a[1..]; }

#elif defined test_missing_lower_bound
typedef int IntSlice[..];
void f(void) { int a[3]; IntSlice s = a[..1]; }

#elif defined test_static_full_slice
typedef int IntSlice[..];
int ga[3] = { 1, 2, 3 };
IntSlice g = ga[..];
#endif
