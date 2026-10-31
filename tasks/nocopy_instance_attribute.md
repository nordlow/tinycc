# `@nocopy` Support on Instances

Add `@nocopy` support on instance declarations and variables. This
has the same effect as an instance of a type with copying disabled,
similar to D's `@disable this(this);`.

## Goal

- Accept `@nocopy` as a variable attribute/modifier (`@nocopy T x;` or
  `T x @nocopy;`) in D language mode (`-lang=d`).
- Record the non-copyable attribute in the symbol table (`Sym` /
  `AttributeDef` / `CType`).
- Enforce copy restrictions at compile time during assignment (`=`),
  initialization, compound assignment, and parameter passing by value.
- Issue clear diagnostic errors when a `@nocopy` instance is copied.
- Allow moving and explicit address-taking (`&x`).

## Motivation

In systems programming and resource management, preventing accidental
copying or duplication of unique resources (such as file descriptors,
locks, or unique handles) is crucial. While disabling copying on a
type prevents copying of all instances of that type, supporting
`@nocopy` on individual instance declarations allows developers to
enforce non-copyability at the variable or instance level without
requiring a custom wrapper struct or disabling copying globally across
all instances of a type.

## Surface Syntax

Gated on `-lang=d` mode:

```c
@nocopy File f1 = open_file("log.txt");
File f2 @nocopy = open_file("data.bin");

// f1 = f2;        /* Error: copying a @nocopy instance */
// process(f1);    /* Error: passing @nocopy instance by value */
process(&f1);      /* OK: passing pointer / address */
```

- `@nocopy` is parsed by `parse_d_attributes()` (`tccgen.c`) alongside
  other attributes like `@noinit`, `@pure`, etc.
- Supported both as a prefix attribute (`@nocopy T x`) and suffix
  modifier (`T x @nocopy`).

## Implementation Plan

### Phase 1: Lexer & Attribute Definitions

1. **Token definition (`tcctok.h`):**
   - Register `TOK_nocopy` if not already present, or handle it as a
     contextual/D attribute keyword in `parse_d_attributes()`.
2. **Attribute structure (`tcc.h`):**
   - Add `int nocopy;` flag to `AttributeDef` struct (where storage
     classes and type attributes are collected).
   - Ensure the attribute propagates from `AttributeDef` to `Sym`
     when symbols are declared (`Sym.nocopy` or `CType.nocopy` /
     `Sym.v`).

### Phase 2: Parsing & Attribute Propagation

1. **`parse_d_attributes()` (`tccgen.c`):**
   - Recognize `@nocopy` when parsing attribute lists before or after
     declarations and set `ad->nocopy = 1`.
2. **Variable Declaration (`decl()` in `tccgen.c`):**
   - When creating the symbol (`external_sym()` or local `sym_push()`),
     copy `ad.nocopy` into the symbol entry (`sym->nocopy = ad.nocopy`
     or store in `Sym` attributes).

### Phase 3: Semantic Checking & Enforcement

1. **Assignment and Initialization (`gassign()` / `store()` in `tccgen.c`):**
   - When generating an assignment `lvalue = rvalue`, inspect whether
     the source or destination expression references a symbol marked
     with `nocopy`.
   - If the source is a `@nocopy` instance being copied (i.e. loaded
     by value rather than referenced/moved), emit a compile error:
     `"cannot copy @nocopy instance '%s'"` via
     `tcc_error_noabort()`.
2. **Function Argument Passing (`indir` / call arguments):**
   - When passing arguments by value to functions, check if the
     argument expression has the `nocopy` flag set. If passed by
     value, reject with an error. Passing by pointer (`&x`) or by `ref`
     is allowed.

## Acceptance Criteria

- Support for `@nocopy` attribute in prefix and suffix forms.
- Compile-time error emission on illegal copying, assignment, or
  pass-by-value of `@nocopy` instances.
- Successful building and regression test suite under `tests/tests2/`.
