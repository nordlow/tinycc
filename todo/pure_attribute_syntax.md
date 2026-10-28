# Syntax for D-Like Function Attributes

Add syntax support for D-style `@pure` function attribute.

Introduce parsing support for D-like builtin attributes, starting with
`@pure` on function declarations and definitions as

    int f(int x) @pure { return x; }
    int g(int x) @pure;

where the `@pure` qualifier must be placed directly after the
parameter list.

Write the implementation in such a way that it becomes easy to add
support for multiple attributes in subsequent changes.
