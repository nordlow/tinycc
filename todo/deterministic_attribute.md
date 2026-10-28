# `@deterministic` / `@det` function attribute

Introduce a new function/scope attribute `@deterministic` (short alias
`@det`) that restricts pointer usage to prevent non-deterministic
behavior.

## Restrictions

In `@deterministic` functions or scopes:

- Pointers may only be used for array/slice indexing and slicing
  operations.
- Pointers **cannot** be used for
  - raw pointer arithmetic
  (`p + n`, `p - n`, `p1 - p2`, `++p`, `--p`),
  - pointer comparisons (`p1 < p2`, etc.),
  - pointer-to-integer casts (e.g., casting `void*` to `size_t` or
    `uintptr_t`),

  or any operation that inspects or depends on raw
  memory addresses.

## Rationale Prevent `@pure` and deterministic code from inadvertently
depending on memory/allocator-dependent pointer addresses, which vary
across runs and violate determinism.
