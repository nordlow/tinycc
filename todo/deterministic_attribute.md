# `@deterministic` / `@det` function attribute

Add a function/scope attribute `@deterministic` (alias `@det`) that
forbids operations whose result depends on raw memory addresses, so
that code in its scope cannot vary with allocator behavior, ASLR, or
stack layout.

## Rationale

`@pure` code (and deterministic code generally) must not inadvertently
depend on pointer addresses, which differ across runs and platforms.
Address-dependent results (ordering by address, hashing addresses,
printing addresses) silently break reproducibility.

## Allowed

- Dereference (`*p`, `p->f`), assignment, and passing pointers.
- Array/slice indexing and slicing (`p[i]`, `&p[i]`, `p[a..b]`),
  despite their desugaring to offset arithmetic.
- Pointer equality with null (`p == NULL`, `!p`).

## Forbidden (compile-time error)

- Raw pointer arithmetic: `p + n`, `p - n`, `p1 - p2`, `++p`, `--p`,
  `p += n`.
- Relational comparison: `p1 < p2`, `<=`, `>`, `>=`.
- Equality between two non-null pointers (`p1 == p2`). [DECIDE]
- Pointer <-> integer casts in either direction (`size_t`, `uintptr_t`,
  `intptr_t`, any integer type).
- Formatting or hashing a pointer value (`%p`, pointer used as hash
  input or ordered-map key).
- Reinterpreting pointer bits via `union` punning or `memcpy`/`memcmp`
  of pointer objects.
- Calling non-`@det` functions (including extern/libc) unless declared
  `@det` or marked with an explicit escape hatch.

## Open questions

- Does `@pure` imply `@det`? (Suggested: yes.)
- Scope of the guarantee: pointer-address independence only, or also
  no `rand()`, `time()`, uninitialized reads, threading? If the former,
  consider naming it `@addr_independent` or documenting the limit.
- Block syntax (`@det { ... }`) and inheritance into lambdas and
  macro expansions.
- Escape hatch for runtime/allocator code (e.g. `@trusted`).
- Function pointers: forbid comparison and casting?
- Is `malloc`/allocation callable from `@det` code?
- Diagnostics: one error per forbidden category with a fix-it hint
  ("use slice indexing instead of pointer arithmetic").

## Tests

- One negative test per forbidden operation; positive tests for
  indexing, slicing, null checks, and dereference.
- Verify `p[i]` and `&p[i]` are accepted while `*(p + i)` is rejected.
