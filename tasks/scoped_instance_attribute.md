# `@scoped` Support on Instances

Add `@scoped` support on instance declarations, similar to D's
`scope` attribute for variables and instances.

## Goal

- Accept `@scoped` as a variable attribute/modifier (`@scoped T x;` or
  `T x @scoped;`) in D language mode (`-lang=d`).
- Track scope boundaries and nesting levels for local variables and
  instances.
- Enforce escape analysis rules at compile time: prevent `@scoped`
  instances or references from escaping their enclosing scope (e.g.
  via assignment to outer/global variables, returning from a
  function, or capturing in heap allocations).
- Issue precise diagnostic errors on scope violations.

## Motivation

In systems programming, ensuring that resources or objects do not
escape their enclosing scope (preventing heap escape, dangling
pointers, or reference leaks) is essential for memory safety and
deterministic lifetime management. D's `scope` storage class ensures
that references or instances cannot escape the scope in which they
are defined, enabling stack allocation guarantees and preventing
lifetime mismatches.

## Surface Syntax

Gated on `-lang=d` mode:

```c
void foo() {
    @scoped Buffer buf = allocate_buffer();
    // global_buf = buf;    /* Error: @scoped instance escapes scope */
    // return buf;          /* Error: returning @scoped instance */
    use_buffer(&buf);       /* OK: remains within local scope */
}
```

- `@scoped` is parsed by `parse_d_attributes()` (`tccgen.c`).
- Supported both as a prefix attribute (`@scoped T x`) and suffix
  modifier (`T x @scoped`).

## Implementation Plan

### Phase 1: Lexer & Attribute Definitions

1. **Token definition (`tcctok.h`):**
   - Register `TOK_scoped` or handle as a D attribute keyword.
2. **Attribute structure (`tcc.h`):**
   - Add `int scoped;` flag to `AttributeDef` and `Sym` structs to mark
     variables and instances as scoped.

### Phase 2: Parsing & Scope Tracking

1. **`parse_d_attributes()` (`tccgen.c`):**
   - Recognize `@scoped` in `parse_d_attributes()` and set
     `ad->scoped = 1`.
2. **Scope Nesting Depth (`Scope` struct in `tcc.h` / `tccgen.c`):**
   - Track block depth or scope level (`scope_level` / `local_stack`)
     for each declared symbol.
   - Record the scope depth at which a `@scoped` instance is declared.

### Phase 3: Escape Analysis & Semantic Checks

1. **Assignment Checks (`gassign()` in `tccgen.c`):**
   - Check assignments where a `@scoped` variable is assigned to a
     target with a broader lifetime (global variables, static variables,
     heap-allocated buffers, or variables declared at an outer scope
     level with a smaller nesting depth).
   - Emit compile error: `"@scoped instance '%s' cannot escape its scope"`
     via `tcc_error_noabort()`.
2. **Return Statement Checks (`parse_return()` in `tccgen.c`):**
   - When returning an expression from a function, if the expression
     references a `@scoped` variable or instance declared inside the
     function scope, emit a compile error:
     `"cannot return @scoped variable '%s'"` via
     `tcc_error_noabort()`.

## Acceptance Criteria

- Support for `@scoped` attribute on local instance definitions.
- Compile-time escape analysis detecting assignments to wider scopes
  and returns of scoped variables.
- Successful building and regression test suite under `tests/tests2/`.
