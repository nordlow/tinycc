#include <stddef.h>

typedef int[..] IntSlice;
typedef char[..] Str;
typedef wchar_t[..] WStr;

#if defined test_char_to_int
IntSlice s = "hi";

#elif defined test_wide_to_char
Str s = L"hi";

#elif defined test_narrow_to_wide
WStr w = "hi";

#elif defined test_mixed_merging
Str s = "a" L"b";
#endif
