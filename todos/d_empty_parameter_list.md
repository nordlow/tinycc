# Allow `void f()` in place of `void f(void)` when `-lang=d`

When `-lang=d` is passed, `void f()` should be allowed in place of
`void f(void)` (an empty parameter list in D means no parameters,
whereas in ISO C it means an unspecified parameter list / old-style
K&R function).

Note that this might already be allowed in default mode.
