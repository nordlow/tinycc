# Task: Bounded Scope Stack for Lexical and Function State

## Goal

Replace the flat per-function TLS globals (`func_vt`, `func_var`,
`func_safety`, `func_vc`, `func_ind`, `funcname`, `func_old`) with
fields of a fixed-capacity stack of lexical scope frames, so that

- block-level attributes (`@safe { ... }`) apply to exactly one
  block and to everything nested in it,
- nested functions can later push their own frame without
  corrupting the enclosing function, and
- scope nesting is bounded and exceeding the bound is diagnosed
  instead of exhausting the C stack.

## Current state

`tccgen.c` already has a lexical scope stack: `struct scope`
(`tccgen.c:125`) with `cur_scope` / `loop_scope` / `root_scope`,
pushed by `new_scope()` (`tccgen.c:8266`) for compound statements,
`for` and `foreach`, and popped by `prev_scope()`
(`tccgen.c:8280`).  `new_scope_s()` (`tccgen.c:8318`) only bumps
`local_scope` for the `if` / `while` / `switch` / `do` conditions;
it pushes no frame.

The function state is still flat `ST_DATA` TLS
(`tccgen.c:73-79`, declared in `tcc.h:1503-1507`).  Five of the
seven variables are read by the target backends:

| Variable     | Backend readers                                            |
|--------------|------------------------------------------------------------|
| `func_vt`    | i386, x86_64, arm, arm64, riscv64, c67                      |
| `func_var`   | arm                                                         |
| `func_vc`    | i386, arm, arm64                                            |
| `func_ind`   | none (debug info and ELF size only)                         |
| `funcname`   | none (diagnostics and `__func__`)                           |

`func_safety` has exactly three readers, all in `tccgen.c`:
pointer arithmetic (`gen_op`, `tccgen.c:3248`), `++` / `--`
(`inc`, `tccgen.c:4173`) and pointer indexing (`[`,
`tccgen.c:7295`).

`block()` already parses D attributes in statement position
(`tccgen.c:8723`) but drops the `AttributeDef` as soon as the block
starts, which is why `@safe { ... }` currently has no effect.

`func_vt` is overloaded: `decl0()` assigns the *function* type to it
(`tccgen.c:11328`) so that the K&R parameter list can be found
again at `tccgen.c:11412` via `func_vt.ref->next`.

## Design

1. **One stack, not two.**  Extend the existing `struct scope`
   instead of adding a parallel `struct Scope`; the lowercase
   struct already is the lexical scope stack.
2. **Fixed capacity.**  `MAX_SCOPE_DEPTH` (256) frames in a TLS
   array; slot 0 is a file-scope sentinel so `cur_scope` is never
   NULL and `func_*` is always readable.  Exceeding the limit is a
   normal `tcc_error`, not a stack overflow.
3. **Inheritance by copy.**  `new_scope()` copies its parent frame,
   so every block inherits return type, variadic flag, name and
   safety level; popping restores the parent by unwinding.
4. **Backends unchanged.**  Keep `func_vt` and friends as macros
   into `cur_scope->fn`, so no target code and no target ABI
   changes.
5. **Block attributes.**  `@safe { ... }` writes the safety level
   of the frame it pushes; `@system { ... }` and `@trusted { ... }`
   override an enclosing `@safe` for their block.
6. **Function frames.**  `gen_function()` pushes a zeroed function
   frame whose parent is the enclosing scope and restores all
   per-function state on exit, so nesting cannot corrupt the host
   function.

## Changes

### `tcc.h`
- Define `struct FuncState` and `struct scope`, `MAX_SCOPE_DEPTH`
  and the `cur_scope` / `loop_scope` / `root_scope` declarations.
- Replace the five `ST_DATA` declarations with `func_*` macros.

### `tccgen.c`
- Remove the flat definitions; add the TLS array and depth counter.
- `new_scope()` returns the pushed frame; `prev_scope()` pops it
  and checks stack balance.
- Add `new_function_scope(Sym *)`; use it in `gen_function()`
  together with save/restore of `local_stack`,
  `local_label_stack`, `global_label_stack`, `all_cleanups`,
  `pending_gotos`, `cur_switch`, `rsym`, `nb_temp_local_vars`,
  `local_scope`, `loc`, `ind`, `nocode_wanted`, `cur_text_section`
  and the scope pointers.  At file scope keep the existing
  "NULL text section after a function" crash guard.
- `block()`: carry the parsed `AttributeDef` into the compound
  block frame.
- `decl0()`: replace the `func_vt = type` K&R hack with an
  explicit parameter-list symbol.

## Non-goals
- Allowing nested function definitions, static chains and
  trampolines; that is `tasks/support_nested_functions.md`.  This
  task only makes the state safe to nest.
- Attributes on non-compound statements (`@safe x++;`).

## Tests
- `tests/tests2/398_scope_attributes.c` (+ `.expect`, with `-dt
  -lang=d`): `@safe` / `@system` / `@trusted` blocks, inheritance
  into nested blocks and `if` bodies, no leakage after the block,
  and the three checked operations (arith, inc, index).
- `tests/tests2/399_scope_depth_error.c` (+ `.expect`): nesting
  more blocks than `MAX_SCOPE_DEPTH` is rejected with a clear
  error.
- Existing `379_d_safety`, `381_d_safety_pointer_arith`,
  `358_d_scope_exit`, `359_c_scope_identifier` and
  `373_scope_guards_error` must pass unchanged.

## Acceptance criteria
- No flat `func_*` variable remains; all seven live in
  `struct scope`.
- Target backends compile unchanged.
- `@safe` applies to a block and does not leak out of it.
- Scope nesting is bounded; exceeding the bound is diagnosed.
- `make -j$(nproc) && make -j$(nproc) test` passes and
  `make pgo PGO_CC=clang` shows no significant throughput or
  instruction-count regression.
