# Support D-style `.sizeof` property on both types and instances

- **Goal**: Allow D-style `.sizeof` property syntax on both type
  identifiers/specifiers (e.g. `int.sizeof`) and expression instances
  (e.g. `x.sizeof`), translating them to standard `sizeof(...)`.
- **Scope**:
  - Support `typename.sizeof` at compile-time where `typename` is a type
    (e.g., `int.sizeof`, `struct Foo.sizeof`).
  - Support `instance.sizeof` where `instance` is an expression/variable
    (e.g., `x.sizeof`, `arr[0].sizeof`).
- **Rationale**:
  - Brings D-style property syntax consistency to type and object size
    evaluation.
  - Interoperability and ergonomic enhancement for D features or
    extensions in TinyCC.
- **Implementation Strategy**:
  - In the lexer/parser/expression parser, recognize `.sizeof` member
    access syntax following either a type expression or an expression
    term, desugaring it into the equivalent `sizeof(type)` or
    `sizeof(expr)`.
