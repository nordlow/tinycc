# Allow `@noinit;` in place of `= void;` in variable definitions

Allow `@noinit;` (both as an initializer `= @noinit;` and as a variable attribute/modifier `@noinit int x;` or `int x @noinit;`) in place of D's `= void;` for declaring uninitialized local and global variables without default-initialization or zero-initialization overhead.

## Motivation

In D and systems programming languages, declaring a variable without initialization (`int x = void;`) avoids the performance cost of zero-initializing or default-initializing memory when the variable is guaranteed to be assigned before use. Providing `@noinit` as a cleaner, attribute-based syntax (`@noinit int x;`, `int x @noinit;`, or `int x = @noinit;`) as well as supporting `= void;` enables precise control over variable initialization overhead.

## Proposed Syntax and Semantics

1. **Initializer syntax:**
   - `int x = void;` (D compatibility)
   - `int x = @noinit;`
2. **Attribute / Modifier syntax:**
   - `@noinit int x;`
   - `int x @noinit;`

### Semantics
- Variables declared with `@noinit` or `= void` / `= @noinit` are left uninitialized (`has_init = 0`).
- For local variables, no zero-initialization code is emitted.
- For global variables, uninitialized storage is placed in BSS (`SHT_NOBITS`).

## Implementation Details

1. **`tcc.h` (`AttributeDef`):**
   - Add `int noinit;` flag to `AttributeDef`.
2. **`tccgen.c` (`parse_d_attributes`):**
   - Recognize `@noinit` in `parse_d_attributes` and set `ad->noinit = 1`.
3. **`tccgen.c` (`decl`):**
   - Check if `ad.noinit` is set, and set `has_init = 0`.
   - When parsing `=`: check if the next token is `TOK_VOID` or `noinit`, consume it, and set `has_init = 0`.

## Acceptance Criteria

- Support for `= void;`, `= @noinit;`, `@noinit int x;`, and `int x @noinit;`.
- Regression test suite under `tests/tests2/` covering local and global variable definitions with `@noinit` and `= void`.
- Successful verification via `make -j$(nproc) && make -j$(nproc) test`.
