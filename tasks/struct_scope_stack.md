# Task: Add `struct Scope` Stack for Lexical and Function State

## Goal
Introduce a `struct Scope` type and a stack of scopes to
encapsulate compiler state currently stored in flat global variables
(such as `func_safety`, `func_var`, `func_vc`, `func_ind`, `func_vt`,
and `funcname`), preparing for robust support of D-style nested
functions and block-level attribute scoping.

## Motivation
Currently, function-level attributes and state (e.g., `func_safety`,
`func_var`) are maintained via global variables in `tccgen.c`. When
parsing nested functions or block-level scopes (such as compound
statements with `@safe`, `@system`, or `@trusted` attributes), flat
globals cannot represent nested lexical contexts or outer function
environments. A stack of `struct Scope` frames will allow clean push
and pop operations during function and block parsing.

## Affected Symbols & Global State
The refactoring will replace the following flat global variables in
`tccgen.c` with fields inside `struct Scope`:
- `func_vt` (`CType`): Current function return type.
- `func_var` (`int`): Flag indicating if the current function is
  variadic (ellipsis).
- `func_safety` (`int`): Function safety level (`FUNC_SAFETY_SAFE`,
  `FUNC_SAFETY_SYSTEM`, `FUNC_SAFETY_TRUSTED`).
- `func_vc` (`int`): Stack address for implicit struct return storage.
- `func_ind` (`int`): Function start address in the text section.
- `funcname` (`const char *`): Name of the current function (used in
  warnings and diagnostics).
- `func_old` (`int`): Flag for old-style K&R parameter declarations.

## Compiler Parts to Refactor (`tccgen.c`)

### 1. Function Definition & Generation (`gen_function`)
- When starting a function compilation (`gen_function`), allocate or
  push a new `Scope` frame, populating its fields from the function
  symbol's attributes (`func_safety`, `func_type`, return type, etc.).
- When finishing the function, pop the scope and restore the parent
  scope.

### 2. Return Checking and Generation (`gfunc_return`, `check_func_return`, and `TOK_RETURN`)
- Update return statement parsing, implicit return injection, and
  return value generation to query `func_vt`, `func_var`, `func_vc`, and
  `funcname` from the active scope rather than globals.

### 3. Safety Check Enforcement (`tccgen.c`)
- Update pointer arithmetic, pointer increment/decrement, and pointer
  indexing checks (`func_safety == FUNC_SAFETY_SAFE`) to inspect the
  safety level of the current enclosing scope.

### 4. Parameter Processing & K&R Declarations (`decl0`)
- Update parameter lookup and type validation (e.g., checking
  `func_vt.ref->next` during parameter declarations) to reference the
  current scope's function return type and parameter list.

### 5. Preparation for Nested Functions (`tasks/support_nested_functions.md`)
- Allow block-level and nested function definitions to push new
  `Scope` instances onto the scope stack, permitting inner functions to
  lexically shadow or coexist with outer function states without
  corrupting enclosing function contexts.

## Acceptance Criteria
- `struct Scope` is defined and managed as a stack.
- All flat global state variables (`func_vt`, `func_var`,
  `func_safety`, `func_vc`, `func_ind`, `funcname`, `func_old`) are
  encapsulated in `struct Scope`.
- All existing tests (including `@safe` safety checks) pass without
  regression.
- Clean foundation established for nested function static chains and
  block-level attribute scoping.
