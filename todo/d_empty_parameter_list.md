# Allow `void f()` in place of `void f(void)` when `-lang=d`

When `-lang=d`, treat an empty parameter list `()` as taking no
arguments (like C++ and D), rather than an unspecified K&R parameter
list.

*Note:* Check if this is already default behavior in TCC. If so,
ensure it isn't accidentally overridden by strict C modes.
