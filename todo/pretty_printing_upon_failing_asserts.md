# Pretty-printing upon failing asserts

When an assertion of the form `assert($L $BOP $R)` fails, diagnose the
values of `$L` and `$R` as conveniently as possible.

For instance, when `$BOP` is `==`, the diagnosis becomes `$L != $R`
showing the actual evaluated values of `$L` and `$R`.
