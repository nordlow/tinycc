# Activate `@safe` memory checks across all language modes

Enable `@safe` annotation support and its associated memory safety
checks (forbidding pointer arithmetic and indexing) across all
language modes (not restricted to `-lang=d`).

Unannotated functions (`FUNC_SAFETY_UNKNOWN`) default to `@system`
semantics (permitting pointer arithmetic and indexing), preserving
backward compatibility with standard C code while allowing `@safe`
contracts to be enforced universally when explicitly specified.
