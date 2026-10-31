# `@scoped` Support on Instances (Transitive by Default)

Add `@scoped` support on instance declarations, drawing inspiration from
Pony's transitive reference guarantees rather than D's weaker,
non-transitive `scope` semantics.

## Design Decision: Transitivity

**Should `@scoped` be transitive? Yes.**

D's `scope` attribute has historically suffered from non-transitivity
gaps (addressed piecemeal in later D language proposals like DIP1000),
where an object itself is scoped but pointers or references stored
inside its fields could escape.

Taking inspiration from Pony's type system—where reference capabilities
and isolation guarantees apply transitively across the entire object
graph reachable through fields—`@scoped` in tinypc MUST be **transitive
by default**:

1. **Transitive Lifetime Bounds:** If an instance `x` is marked
   `@scoped`, every pointer, reference, or aggregate field transitively
   reachable from `x` inherits the scoped lifetime constraint.
2. **Leak Prevention:** Extracting or assigning a pointer/reference field
   from a `@scoped` instance to any destination with a broader
   lifetime (global variables, heap allocations, or outer scopes) is a
   compile-time error.

## Goal

- Accept `@scoped` as a variable attribute/modifier (`@scoped T x;` or
  `T x @scoped;`) in D language mode (`-lang=d`).
- Enforce **transitive** escape analysis at compile time: prevent
  `@scoped` instances and any transitively nested references from
  escaping their enclosing scope.
- Issue precise diagnostic errors on scope violations.

## Surface Syntax

Gated on `-lang=d` mode:

```c
struct Node {
    int *ptr;
};

void foo() {
    int local_val = 42;
    @scoped struct Node n;
    n.ptr = &local_val;  /* OK: both scoped / local */

    // global_ptr = n.ptr; /* Error: transitive escape of scoped reference */
    // return n.ptr;       /* Error: returning pointer from scoped instance */
}
```

## Implementation Plan

### Phase 1: Lexer & Attribute Definitions

1. **Token definition (`tcctok.h`):**
   - Register `TOK_scoped` or handle as a D attribute keyword.
2. **Attribute structure (`tcc.h`):**
   - Add `int scoped;` flag to `AttributeDef`, `Sym`, and `CType`
     structs to mark types, variables, and instances as transitively
     scoped.

### Phase 2: Parsing & Propagation

1. **`parse_d_attributes()` (`tccgen.c`):**
   - Recognize `@scoped` in `parse_d_attributes()` and set
     `ad->scoped = 1`.
2. **Transitive Type Qualification (`CType`):**
   - When a struct or pointer type contains or is qualified with
     `@scoped`, propagate the scoped property transitively to member
     accesses (`.` and `->`).

### Phase 3: Transitive Escape Analysis & Checks

1. **Assignment & Field Extraction Checks (`gassign()` & member access):**
   - When accessing fields of a `@scoped` instance (`n.ptr`), ensure the
     resulting expression retains the scoped/restricted provenance.
   - Disallow assigning or copying such scoped references to targets
     with wider lifetimes (globals, statics, outer scopes).
   - Emit compile error: `"transitive escape of @scoped reference '%s'"`
     via `tcc_error_noabort()`.
2. **Return Statement Checks (`parse_return()` in `tccgen.c`):**
   - Disallow returning any `@scoped` instance or any pointer/reference
     extracted from a `@scoped` instance.

## Acceptance Criteria

- Transitive `@scoped` attribute enforcement on local instances and
  their fields.
- Compile-time error emission on transitive escape of scoped references.
- Regression test suite under `tests/tests2/`.
