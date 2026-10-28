# Activate `@safe` memory checks across all language modes

Enable `@safe` / `@system` / `@trusted` annotations and the `@safe`
memory checks in every language mode, not just `-lang=d`.

## Invariants
- Unannotated functions (`FUNC_SAFETY_UNKNOWN`) behave as `@system`:
  pointer arithmetic and indexing remain allowed. No existing C
  program may change behavior.
- Only functions explicitly marked `@safe` are checked.
- Slice indexing/slicing remains legal in `@safe`; only raw pointer
  arithmetic/indexing is forbidden.
